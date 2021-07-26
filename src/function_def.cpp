#include "function_def.hpp"
#include <string>
#include <iostream>
#include <map>
    
void FunctionDef::print(std::ostream& out) const {
    out << "FunctionDef(";
    out << " Id: " << id;
    out << " Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << ", Par_list: ";
    if(par_list != nullptr)
        par_list->print(out);
    else
        out << "null ";
    out << ", Expr: ";
    if(expr != nullptr)
        expr->print(out);
    else
        out << "null ";
    out << ") ";
}

void FunctionDef::add_to_symbol_table() {
    FunctionEntry* entry = new FunctionEntry(id, EntryType::ENTRY_FUNCTION, this->from_type, this->type_variable, this->par_list->block_size());
    
    st->insert_entry(entry);

    this->entry = entry;
}

void FunctionDef::allocate() {
    //TODO: Construct struct of all types in current scope
    //Create a function prototype
    auto func_entry = dynamic_cast<FunctionEntry*>(this->entry);

    auto pointer_to_func_type = llvm::dyn_cast<llvm::PointerType>(map_to_llvm_type(this->entry->get_type()));
    auto function_type = llvm::dyn_cast<llvm::FunctionType>(pointer_to_func_type->getElementType());
    auto function_declaration = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, id+"_"+std::to_string(func_entry->get_count()), TheModule.get());

    auto par_list = this->par_list->get_list();
    std::vector<llvm::Type*> par_list_types;
    int i = 0;
    for(auto &par: function_declaration->args()) {
        if(i <= par_list.size() - 1)
            par.setName(par_list[i++]->get_id());
        else
            par.setName("non_locals");
    }

    func_entry->set_allocation(Builder.CreateAlloca(pointer_to_func_type, nullptr, id+"_function"));
    func_entry->set_function_declaration(function_declaration);
}

std::shared_ptr<TypeVariable> FunctionDef::infer() {
    FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(this->entry);

    //Function scope includes parameters and body
    st->scope_open(); 

    std::shared_ptr<TypeVariable> from_type = this->par_list->infer();
    this->from_type = from_type;

    //Function from type must be the same as the type of its parameter list.
    st->add_constraint(func_entry->get_from_type(), from_type);

    std::shared_ptr<TypeVariable> to_type = this->expr->infer();

    //Function return type must be the same as its body expr type.
    st->add_constraint(this->type_variable, to_type);

    st->scope_close();

    return this->type_variable;
}

void FunctionDef::sem() { 
    FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(this->entry);
    auto to_type = func_entry->get_to_type();

    //Function scope includes parameters and body
    st->scope_open(); 

    this->par_list->sem();

    this->pass_stage = PassStage::FunctionDef;
    this->current_func_def_non_locals = &this->non_local_variables;
    this->expr->sem();
    this->pass_stage = PassStage::Other;

    st->scope_close();

    if((sa->is_same_tag(to_type, TypeTag::Function))) {
        std::cerr << "Function " << id << " return type can not be of type function\n" << "offending type is: " << *to_type;
        exit(1); //TODO: Error handling.
    }
    if((sa->is_same_tag(to_type, TypeTag::Array))) {
        std::cerr << "Function " << id << " return type can not be of type array\n" << "offending type is: " << *to_type;
        exit(1); //TODO: Error handling.
    }
}

llvm::Value* FunctionDef::codegen() {
    FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(this->entry);
    auto function = func_entry->get_function_declaration();

    std::vector<llvm::Type*> non_local_struct_types;
    std::vector<llvm::Value*> non_local_struct_allocas;

    non_local_struct_types.push_back(i32);

    for(auto nl_it = this->non_local_variables.begin(); nl_it != this->non_local_variables.end(); nl_it++) {
        auto nl_entry = st->lookup_entry(nl_it->first, LookupType::LOOKUP_ALL_SCOPES);
        auto nl_type = map_to_llvm_type(nl_it->second);
        non_local_struct_types.push_back(llvm::PointerType::get(nl_type, 0));
        non_local_struct_allocas.push_back(nl_entry->get_allocation());
    }

    // Struct structure: { non_local_variable_count, ptr_to_non_local_variable_1, ptr_to_non_local_variable_2, ... }
    auto non_local_struct_type = llvm::StructType::get(TheContext, non_local_struct_types);
    auto non_local_struct = Builder.CreateAlloca(non_local_struct_type, nullptr, id+"_"+std::to_string(func_entry->get_count())+"_non_local_struct");

    auto non_local_count_ptr = Builder.CreateStructGEP(non_local_struct, 0, id+"_"+std::to_string(func_entry->get_count())+"_non_locals_count");
    Builder.CreateStore(c32(this->non_local_variables.size()), non_local_count_ptr);

    //Store pointers to non_local variables in struct.
    unsigned int i = 0;
    for(auto non_local_struct_alloca: non_local_struct_allocas) {
        //Returns a pointer to the struct element which is a pointer to the non local variable
        auto non_local_ref_ptr = Builder.CreateStructGEP(non_local_struct, ++i, id+"_"+std::to_string(func_entry->get_count())+"_non_local_ref_ptr");
        Builder.CreateStore(non_local_struct_alloca, non_local_ref_ptr);
    }

    //Pointer to non_local_struct for use during function calls
    func_entry->set_non_local_struct(Builder.CreateBitCast(non_local_struct, llvm::PointerType::get(i32, 0), id+"_"+std::to_string(func_entry->get_count())+"_non_local_struct_ptr"));

    //Function scope includes parameters and body
    st->scope_open(); 

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, id+"_"+std::to_string(func_entry->get_count())+"_entry", function);
    Builder.SetInsertPoint(function_body_BB);

    auto par_list_vector = this->par_list->get_list();

    //allocate space for all parameters within function body
    std::vector<llvm::Value*> par_allocas;
    for(auto par: par_list_vector) {
        par_allocas.push_back(par->codegen());
    }
    auto non_cast_pointer_to_struct_alloca = Builder.CreateAlloca(llvm::PointerType::get(i32, 0), nullptr, "non_locals_par");

    //store function parameters in local allocas
    i = 0;
    for(auto &par: func_entry->get_function_declaration()->args()) {
        if(i <= par_allocas.size() - 1)
            Builder.CreateStore(&par, par_allocas[i++]);
        else
            Builder.CreateStore(&par, non_cast_pointer_to_struct_alloca);
    }

    //Load pointer to non_local struct and bitcast it to its original type
    auto parent_function_struct_first_element_ptr = Builder.CreateLoad(non_cast_pointer_to_struct_alloca, "parent_function_struct_first_element_ptr");
    auto parent_function_struct_ptr = Builder.CreateBitCast(parent_function_struct_first_element_ptr, llvm::PointerType::get(non_local_struct_type, 0), "parent_function_struct_ptr");
    
    //allocate space in function stack for pointer to non local struct
    auto non_local_struct_function_body = Builder.CreateAlloca(non_local_struct_type, nullptr, "non_local_struct");
    auto struct_ptr = Builder.CreateGEP(parent_function_struct_ptr, { c32(0) }, "struct_ptr");
    Builder.CreateStore(Builder.CreateLoad(struct_ptr, "non_local_struct_load"), non_local_struct_function_body);


    //Load all non local variables and replace their alloca in the symbol table with the ones in the function body
    std::map<std::string, llvm::AllocaInst*> non_local_allocas;
    i = 0;
    for(auto nl_it = this->non_local_variables.begin(); nl_it != this->non_local_variables.end(); nl_it++) {
        //Returns a pointer to the struct element which is a pointer to the non local variable
        auto non_local_ref_ptr = Builder.CreateStructGEP(non_local_struct_function_body, ++i, "non_local_ref_ptr");
        //Dereference both the GEP pointer and the variable pointer to get the type of the non local variable
        auto non_local_alloca = Builder.CreateAlloca(non_local_ref_ptr->getType()->getPointerElementType()->getPointerElementType(),  nullptr, nl_it->first);
        Builder.CreateStore(Builder.CreateLoad(Builder.CreateLoad(non_local_ref_ptr)), non_local_alloca);

        //Remember non local variables old alloca
        auto nl_entry = st->lookup_entry(nl_it->first, LookupType::LOOKUP_ALL_SCOPES);
        non_local_allocas.insert({ nl_it->first, nl_entry->get_allocation() });

        //Store non local alloca in variables symbol table
        nl_entry->set_allocation(non_local_alloca);
    }

    auto return_value = this->expr->codegen();

    if(return_value != nullptr)
        Builder.CreateRet(return_value);
    else
        Builder.CreateRetVoid();

    //return non local variables alloca in the symbol table to their original value
    for(auto nl_it = non_local_allocas.begin(); nl_it != non_local_allocas.end(); nl_it++) {
        auto nl_entry = st->lookup_entry(nl_it->first, LookupType::LOOKUP_ALL_SCOPES);
        nl_entry->set_allocation(nl_it->second);
    }

    Builder.SetInsertPoint(previous_insert_point);

    st->scope_close();

    return function;
}