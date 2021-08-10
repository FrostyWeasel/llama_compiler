#include "constructor.hpp"
#include "type_variable.hpp"
#include "symbol_table.hpp"
#include "block.hpp"
#include "type_entry.hpp"
#include "constructor_entry.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>

unsigned int Constructor::counter = 0;

Constructor::Constructor(std::string* id) : id(*id), type_list(new std::vector<std::shared_ptr<TypeVariable>>()) {
    this->count = Constructor::counter++;
}
Constructor::Constructor(std::string* id, std::vector<std::shared_ptr<TypeVariable>>* type_list) : id(*id), type_list(type_list) {
    this->count = Constructor::counter++;
}

Constructor::~Constructor() {
    delete type_list;
}

void Constructor::print(std::ostream& out) const {
    out << "Constructor(";
    out << " Id: " << id;
    out << " Type_constructed: ";
    if(type_constructed != nullptr)
        type_constructed->print(out);
    else
        out << "null ";
    out << ", types: ";
    if(type_list != nullptr)
        for(auto type: *type_list) {
            type->print(out);
        }
    else
        out << "null ";
    out << ") ";
}

void Constructor::add_to_symbol_table() {

}

void Constructor::add_to_symbol_table(TypeEntry* owner_type) {
    this->type_constructed = owner_type->get_type();

    auto entry = new ConstructorEntry(id, EntryType::ENTRY_CONSTRACTOR, this->type_constructed, count, this->type_list);

    st->insert_entry(entry);
    this->entry = entry;

}

void Constructor::allocate() {
    auto constr_comparison_function_type = llvm::FunctionType::get(i1, { llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0) }, false);
    auto constr_comparison_function = llvm::Function::Create(constr_comparison_function_type, llvm::Function::LinkageTypes::ExternalLinkage, "__"+this->id+"_"+std::to_string(this->count)+"_structural_constr_comparison", TheModule.get());

    this->constructor_structural_cmp_function = constr_comparison_function;
    this->entry->set_constructor_structural_cmp_function(constr_comparison_function);
}

std::shared_ptr<TypeVariable> Constructor::infer() {

    return this->type_constructed;

}

void Constructor::sem() {

}

llvm::Value* Constructor::codegen() {
    std::vector<llvm::Type*> constructor_args_type;

    constructor_args_type.push_back(i32);
    for(auto type: *(this->type_list)) {
        constructor_args_type.push_back(map_to_llvm_type(type));
    }

    auto constructor_type = llvm::StructType::get(TheContext, constructor_args_type);
    this->entry->set_llvm_type(constructor_type);

    //Generate function used for structural comparison of constructor

    auto constr_comparison_function = this->constructor_structural_cmp_function;

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "__"+this->id+"_"+std::to_string(this->count)+"_structural_constr_comparison_entry", constr_comparison_function);
    Builder.SetInsertPoint(function_body_BB);

    auto current_function = Builder.GetInsertBlock()->getParent();

    auto function_end_BB = llvm::BasicBlock::Create(TheContext, "function_end");
    auto comparisons_end_BB = llvm::BasicBlock::Create(TheContext, "comparisons_end");
    auto comparisons_start_BB = llvm::BasicBlock::Create(TheContext, "comparisons_start");
    auto comparison_failed_BB = llvm::BasicBlock::Create(TheContext, "comparison_failed");

    auto constructor_1 = Builder.CreateBitCast(constr_comparison_function->getArg(0), llvm::PointerType::get(constructor_type, 0));
    auto constructor_2 = Builder.CreateBitCast(constr_comparison_function->getArg(1), llvm::PointerType::get(constructor_type, 0));

    Builder.CreateBr(comparisons_start_BB);

    //Used to access constructor struct elements
    unsigned int i = 1;

    //Compare the arguments to see whether they are structurally the same
    current_function->getBasicBlockList().push_back(comparisons_start_BB);
    Builder.SetInsertPoint(comparisons_start_BB);

    if(this->type_list->empty()) {
        //If there are no comparisons then the structural equality is true
        Builder.CreateBr(comparisons_end_BB);    
    }
    else {
        for(auto type: *(this->type_list)) {
            llvm::Value* cmp_result;

            switch(type->get_tag()){
                llvm::Value* value_1;
                llvm::Value* value_2;

                case TypeTag::Int:
                    value_1 = Builder.CreateLoad(Builder.CreateGEP(constructor_1, { c32(0), c32(i) }, "constructor_1_value_ptr"), "constructor_1_value");
                    value_2 = Builder.CreateLoad(Builder.CreateGEP(constructor_2, { c32(0), c32(i) }, "constructor_2_value_ptr"), "constructor_2_value");

                    cmp_result = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, value_1, value_2, "cmp_result");
                    break;

                case TypeTag::Bool:
                    value_1 = Builder.CreateLoad(Builder.CreateGEP(constructor_1, { c32(0), c32(i) }, "constructor_1_value_ptr"), "constructor_1_value");
                    value_2 = Builder.CreateLoad(Builder.CreateGEP(constructor_2, { c32(0), c32(i) }, "constructor_2_value_ptr"), "constructor_2_value");
                    
                    cmp_result = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, value_1, value_2, "cmp_result");
                    break;

                case TypeTag::Char:
                    value_1 = Builder.CreateLoad(Builder.CreateGEP(constructor_1, { c32(0), c32(i) }, "constructor_1_value_ptr"), "constructor_1_value");
                    value_2 = Builder.CreateLoad(Builder.CreateGEP(constructor_2, { c32(0), c32(i) }, "constructor_2_value_ptr"), "constructor_2_value");
                    
                    cmp_result = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, value_1, value_2, "cmp_result");
                    break;

                case TypeTag::Float:
                    value_1 = Builder.CreateLoad(Builder.CreateGEP(constructor_1, { c32(0), c32(i) }, "constructor_1_value_ptr"), "constructor_1_value");
                    value_2 = Builder.CreateLoad(Builder.CreateGEP(constructor_2, { c32(0), c32(i) }, "constructor_2_value_ptr"), "constructor_2_value");
                    
                    cmp_result = Builder.CreateFCmp(llvm::CmpInst::FCMP_OEQ, value_1, value_2, "cmp_result");
                    break;

                case TypeTag::Reference:
                    value_1 = Builder.CreateLoad(Builder.CreateGEP(constructor_1, { c32(0), c32(i) }, "constructor_1_value_ptr"), "constructor_1_value");
                    value_2 = Builder.CreateLoad(Builder.CreateGEP(constructor_2, { c32(0), c32(i) }, "constructor_2_value_ptr"), "constructor_2_value");
                    
                    //for references the pointer to the reference is compared if compairing the type is desired the user can dereference first
                    cmp_result = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, value_1, value_2, "cmp_result");
                    break;

                case TypeTag::Unit:
                    cmp_result = c1(1); 
                    break;

                case TypeTag::Unknown: 
                    cmp_result = c1(1);
                    break;

                case TypeTag::UserType: {
                    value_1 = Builder.CreateLoad(Builder.CreateGEP(constructor_1, { c32(0), c32(i) }, "constructor_1_value_ptr"), "constructor_1_value");
                    value_2 = Builder.CreateLoad(Builder.CreateGEP(constructor_2, { c32(0), c32(i) }, "constructor_2_value_ptr"), "constructor_2_value");
                    
                    auto user_type = dynamic_cast<TypeEntry*>(st->lookup_entry_of_type(type->get_user_type_id(), EntryType::ENTRY_TYPE));
                    cmp_result = Builder.CreateCall(user_type->get_constructor_cmp_function(), { value_1, value_2 });
                    break;
                }
                default: {
                    //Throw runtime error if pattern was matched 
                    std::stringstream msg;
                    msg << "In constructor " << this->id << ": Structural comparison is not defined for constructors with arrays or functions as arguments\n";
                    auto string_ptr = Builder.CreateGlobalStringPtr(msg.str());
                    Builder.CreateCall(AST::runtime_error_function, { string_ptr });

                    cmp_result = c1(0);

                    break;
                }
            }

            if(i == (*this->type_list).size())
                Builder.CreateCondBr(cmp_result, comparisons_end_BB, comparison_failed_BB);
            else {
                auto next_comparison_BB = llvm::BasicBlock::Create(TheContext, "next_comparison", current_function);
                Builder.CreateCondBr(cmp_result, next_comparison_BB, comparison_failed_BB);
                Builder.SetInsertPoint(next_comparison_BB);
            }

            i++;
        }
    }

    //If we reach this point set the value of result equal to true and jump to function end
    current_function->getBasicBlockList().push_back(comparisons_end_BB);
    Builder.SetInsertPoint(comparisons_end_BB);
    auto result_success = c1(1);
    Builder.CreateBr(function_end_BB);

    //If we come here set the value of result equal to false and jump to function end
    current_function->getBasicBlockList().push_back(comparison_failed_BB);
    Builder.SetInsertPoint(comparison_failed_BB);
    auto result_failed = c1(0);
    Builder.CreateBr(function_end_BB);

    //When function ends get the value of the phi node from the comparisons and return it
    current_function->getBasicBlockList().push_back(function_end_BB);
    Builder.SetInsertPoint(function_end_BB);

    auto phi_node_result = Builder.CreatePHI(i1, 2, "comparison_result");
    phi_node_result->addIncoming(result_success, comparisons_end_BB);
    phi_node_result->addIncoming(result_failed, comparison_failed_BB);

    Builder.CreateRet(phi_node_result);
    Builder.SetInsertPoint(previous_insert_point);

    return constr_comparison_function;
}
