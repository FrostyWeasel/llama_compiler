#include "t_def.hpp"
#include "type_variable.hpp"
#include "constructor.hpp"
#include "symbol_table.hpp"
#include "block.hpp"
#include "type_entry.hpp"
#include <string>
#include <memory>
#include <iostream>

unsigned int TDef::counter = 0;

TDef::TDef(std::string* id, Block<Constructor>* constructor_list) : id(*id), constructor_list(constructor_list), type_variable(std::make_shared<TypeVariable>(TypeTag::UserType, *id)) {
    this->count = counter++;
}

TDef::~TDef() {
    delete constructor_list;
}

void TDef::print(std::ostream& out) const {
    out << "TDef(";
    out << " Id: " << id;
    out << " Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << ", constructor_list: ";
    if(constructor_list != nullptr)
        constructor_list->print(out);
    else
        out << "null ";
    out << ") ";
}

void TDef::add_to_symbol_table()  {
    auto entry = new TypeEntry(id, EntryType::ENTRY_TYPE, this->type_variable, this->constructor_list->get_list());

    st->insert_entry(entry);
    this->entry = entry;

    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->add_to_symbol_table(entry);
    }
}

void TDef::allocate()  {
    //Structural comparison function declaration
    auto user_type_comparison_function_type = llvm::FunctionType::get(i1, { llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0) }, false);
    auto user_type_comparison_function = llvm::Function::Create(user_type_comparison_function_type, llvm::Function::LinkageTypes::ExternalLinkage, "__"+this->id+"_"+std::to_string(this->count)+"_structural_type_comparison", TheModule.get());

    this->user_type_comparison_function = user_type_comparison_function;
    this->entry->set_constructor_cmp_function(user_type_comparison_function);

    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->allocate();
    }
}

std::shared_ptr<TypeVariable> TDef::infer() {
    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->infer();
    }

    return this->type_variable;
}

void TDef::sem() {
    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->sem();
    }
}

llvm::Value* TDef::codegen() {
    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        //For each constructor a function i1 (i8*, i8*) is created that takes 2 constructors of the constructors tag and returns true if they are structurally the same and false otherwise
        constructor->codegen();
    }

    //Generate code for structural comparison function
    auto function_decl = this->user_type_comparison_function;

    auto previous_insert_point = Builder.GetInsertBlock();
    auto function_body_BB = llvm::BasicBlock::Create(TheContext, "__"+this->id+"_"+std::to_string(this->count)+"_structural_type_comparison_entry", function_decl);
    Builder.SetInsertPoint(function_body_BB);

    auto current_function = Builder.GetInsertBlock()->getParent();

    auto function_end_BB = llvm::BasicBlock::Create(TheContext, "function_end");
    auto call_constructor_cmp_function_BB = llvm::BasicBlock::Create(TheContext, "call_constructor_cmp_function");
    auto comparisons_success_BB = llvm::BasicBlock::Create(TheContext, "comparisons_success");
    auto comparison_failed_BB = llvm::BasicBlock::Create(TheContext, "comparison_failed");

    //Load constructor tag and see whether they match
    auto constructor_1 = Builder.CreateBitCast(function_decl->getArg(0), llvm::PointerType::get(i32, 0));
    auto constructor_2 = Builder.CreateBitCast(function_decl->getArg(1), llvm::PointerType::get(i32, 0));

    auto constructor_1_tag = Builder.CreateLoad(constructor_1, "constructor_1_tag");
    auto constructor_2_tag = Builder.CreateLoad(constructor_2, "constructor_2_tag");

    auto cmp_tag_result = Builder.CreateICmp(llvm::ICmpInst::Predicate::ICMP_EQ, constructor_1_tag, constructor_2_tag, "compare_constr_tags");
    Builder.CreateCondBr(cmp_tag_result, call_constructor_cmp_function_BB, comparison_failed_BB);

    current_function->getBasicBlockList().push_back(call_constructor_cmp_function_BB);
    Builder.SetInsertPoint(call_constructor_cmp_function_BB);

    auto switch_to_correct_function_call = Builder.CreateSwitch(constructor_1_tag, comparison_failed_BB);

    std::vector<llvm::BasicBlock*> constructor_cmp_func_call_BBs;
    for(auto constructor: constructors) {
        auto constructor_cmp_func_call_BB = llvm::BasicBlock::Create(TheContext, "constructor_"+std::to_string(constructor->get_tag())+"_cmp_func_call");
        switch_to_correct_function_call->addCase(c32(constructor->get_tag()), constructor_cmp_func_call_BB);
        constructor_cmp_func_call_BBs.push_back(constructor_cmp_func_call_BB);
    }

    unsigned int i = 0;
    for(auto constructor_cmp_func_call_BB: constructor_cmp_func_call_BBs) {
        current_function->getBasicBlockList().push_back(constructor_cmp_func_call_BB);
        Builder.SetInsertPoint(constructor_cmp_func_call_BB);

        auto result = Builder.CreateCall(constructors[i++]->get_function_declaration(), { function_decl->getArg(0), function_decl->getArg(1) });
        Builder.CreateCondBr(result, comparisons_success_BB, comparison_failed_BB);
    }

    //If we reach this point set the value of result equal to true and jump to function end
    current_function->getBasicBlockList().push_back(comparisons_success_BB);
    Builder.SetInsertPoint(comparisons_success_BB);
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
    phi_node_result->addIncoming(result_success, comparisons_success_BB);
    phi_node_result->addIncoming(result_failed, comparison_failed_BB);

    Builder.CreateRet(phi_node_result);
    Builder.SetInsertPoint(previous_insert_point);

}