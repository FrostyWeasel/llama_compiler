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
    //Create a function prototype
    auto func_entry = dynamic_cast<FunctionEntry*>(this->entry);

    auto function_struct = llvm::dyn_cast<llvm::StructType>(map_to_llvm_type(this->entry->get_type()));
    auto function_type = llvm::dyn_cast<llvm::FunctionType>(function_struct->getContainedType(0)->getPointerElementType());
    auto function_declaration = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, id+"_"+std::to_string(func_entry->get_count()), TheModule.get());

    auto par_list = this->par_list->get_list();
    std::vector<llvm::Type*> par_list_types;
    unsigned int i = 0;
    for(auto &par: function_declaration->args()) {
        if(i <= par_list.size() - 1)
            par.setName(par_list[i++]->get_id()+"_par");
        else
            par.setName("function_struct_par");
    }

    auto func_struct_alloca = Builder.CreateAlloca(function_struct, nullptr, id+"_"+std::to_string(func_entry->get_count())+"_function_struct");
    func_entry->set_allocation(func_struct_alloca);
    func_entry->set_function_declaration(function_declaration);
    auto func_ptr = Builder.CreateStructGEP(func_struct_alloca, 0, id+"_"+std::to_string(func_entry->get_count())+"_function_ptr");
    Builder.CreateStore(function_declaration, func_ptr);

}


void FunctionDef::make_non_local_variable_stack() {
    FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(this->entry);

    std::vector<llvm::Type*> non_local_struct_types;
    std::vector<llvm::Value*> non_local_struct_allocas;

    for(auto nl_it = this->non_local_variables.begin(); nl_it != this->non_local_variables.end(); nl_it++) {
        auto nl_entry = st->lookup_entry(nl_it->first, LookupType::LOOKUP_ALL_SCOPES);
        auto nl_type = map_to_llvm_type(nl_it->second);
        non_local_struct_types.push_back(llvm::PointerType::get(nl_type, 0));
        non_local_struct_allocas.push_back(nl_entry->get_allocation());
    }

    // Struct structure: { non_local_variable_count, ptr_to_non_local_variable_1, ptr_to_non_local_variable_2, ... }
    auto non_local_struct_type = llvm::StructType::get(TheContext, non_local_struct_types);
    this->non_local_struct_type = non_local_struct_type;
    auto non_local_struct = Builder.CreateAlloca(non_local_struct_type, nullptr, id+"_"+std::to_string(func_entry->get_count())+"_non_locals_struct");

    //Store pointers to non_local variables in struct.
    unsigned int i = 0;
    for(auto non_local_struct_alloca: non_local_struct_allocas) {
        //Returns a pointer to the struct element which is a pointer to the non local variable
        auto non_local_ref_ptr = Builder.CreateStructGEP(non_local_struct, i++, id+"_"+std::to_string(func_entry->get_count())+"_non_local_variable_struct_ptr");
        Builder.CreateStore(non_local_struct_alloca, non_local_ref_ptr);
    }

    //Pointer to non_local_struct for use during function calls
    auto ptr_to_non_local_struct = Builder.CreateBitCast(non_local_struct, llvm::PointerType::get(i8, 0), id+"_"+std::to_string(func_entry->get_count())+"_non_locals_struct_ptr");
    auto func_struct_non_locals_ptr = Builder.CreateStructGEP(func_entry->get_allocation(), 1, id+"_"+std::to_string(func_entry->get_count())+"_func_struct_non_locals_ptr");
    Builder.CreateStore(ptr_to_non_local_struct, func_struct_non_locals_ptr);
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

    //get list of non local variables in function body
    auto is_outer_scope_function_def = false;
    if(this->pass_stage != PassStage::FunctionDef)
        this->pass_stage = PassStage::FunctionDef;
    else
        is_outer_scope_function_def = true;

    AST::current_func_def_non_locals = &this->non_local_variables;
    this->expr->sem();

    //Make sure that no non local variable is a parameter of the function. If it is remove it
    auto par_vector =  this->par_list->get_list();
    for(auto par: par_vector) {
        if(this->non_local_variables.count(par->get_id()) != 0)
            this->non_local_variables.erase(par->get_id());
    }

    //Make sure that non local variable has an earlier definition than this function definition but is also not a library function
    std::vector<std::string> out_of_scope_variables;
    for(auto nl: this->non_local_variables) {
        auto is_in_table = st->contains(nl.first, LookupType::LOOKUP_ALL_SCOPES);
        if(!is_in_table){
            out_of_scope_variables.push_back(nl.first);
        }
        else{
            auto non_local_variable_entry = st->lookup_entry(nl.first, LookupType::LOOKUP_ALL_SCOPES);
            if(non_local_variable_entry->get_nesting_level() == 1)
                out_of_scope_variables.push_back(nl.first);
        }
    }
    for(auto out_of_scope_variable_id: out_of_scope_variables) {
        this->non_local_variables.erase(out_of_scope_variable_id);
    }

    if(!is_outer_scope_function_def)
        this->pass_stage = PassStage::Other;

    st->scope_close();

    if((sa->is_same_tag(to_type, TypeTag::Function))) {
        std::cerr << "Function " << id << " return type can not be of type function\n" << "offending type is: " << *to_type;
        exit(1); //TODO: Error handling.
    }
    // if((sa->is_same_tag(to_type, TypeTag::Array))) {
    //     std::cerr << "Function " << id << " return type can not be of type array\n" << "offending type is: " << *to_type;
    //     exit(1); //TODO: Error handling.
    // }
}

llvm::Value* FunctionDef::codegen() {
    FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(this->entry);
    auto function = func_entry->get_function_declaration();
    auto func_struct = func_entry->get_allocation();

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
    auto func_struct_alloca = Builder.CreateAlloca(func_struct->getType(), nullptr, "function_struct");

    //store function parameters in local allocas
    unsigned int i = 0;
    for(auto &par: func_entry->get_function_declaration()->args()) {
        if(i <= par_allocas.size() - 1)
            Builder.CreateStore(&par, par_allocas[i++]);
        else {
            Builder.CreateStore(Builder.CreateBitCast(&par, func_struct->getType()), func_struct_alloca);
        }
    }

    //Load pointer to non_local struct and bitcast it to its original type
    auto non_locals_struct_first_element_ptr = Builder.CreateStructGEP(Builder.CreateLoad(func_struct_alloca, "function_struct_load"), 1, "non_locals_struct_first_element_ptr");
    auto non_locals_struct_first_element_ptr_load = Builder.CreateLoad(non_locals_struct_first_element_ptr, "non_locals_struct_first_element_ptr_load");
    auto non_locals_struct_ptr = Builder.CreateBitCast(non_locals_struct_first_element_ptr_load, llvm::PointerType::get(non_local_struct_type, 0), "non_locals_struct_ptr");
    
    //allocate space in function stack for pointer to non local struct
    auto non_locals_struct = Builder.CreateAlloca(non_local_struct_type, nullptr, "non_locals_struct");
    Builder.CreateStore(Builder.CreateLoad(non_locals_struct_ptr, "non_local_struct_load"), non_locals_struct);


    //Load all non local variables and replace their alloca in the symbol table with the ones in the function body
    std::map<std::string, llvm::AllocaInst*> non_local_allocas;

    i = 0;
    for(auto nl_it = this->non_local_variables.begin(); nl_it != this->non_local_variables.end(); nl_it++) {
        //Returns a pointer to the struct element which is a pointer to the non local variable
        auto non_local_ref_ptr = Builder.CreateStructGEP(non_locals_struct, i++, "non_local_ref_ptr");
        //Dereference both the GEP pointer and the variable pointer to get the type of the non local variable
        auto non_local_alloca = Builder.CreateAlloca(non_local_ref_ptr->getType()->getPointerElementType()->getPointerElementType(),  nullptr, nl_it->first);
        Builder.CreateStore(Builder.CreateLoad(Builder.CreateLoad(non_local_ref_ptr)), non_local_alloca);

        auto nl_entry = st->lookup_entry(nl_it->first, LookupType::LOOKUP_ALL_SCOPES);

        //Remember non local variables old alloca
        non_local_allocas.insert({ nl_it->first, nl_entry->get_allocation() });

        //Store non local alloca in variables symbol table
        nl_entry->set_allocation(non_local_alloca);
    }

    auto return_value = this->expr->codegen();

    if((return_value != nullptr) && (!(function->getReturnType()->isVoidTy())))
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