#include "while.hpp"
#include "type_variable.hpp"
#include "symbol_table.hpp"
#include <iostream>

While::While(Expr* condition, Expr* expr): condition(condition), expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}

While::~While() {
    delete condition;
    delete expr;
}

void While::print(std::ostream &out) const {
    out << "While(";
    out << "Condition: ";
    if(condition != nullptr)
        condition->print(out);
    else
        out << "null ";
    out << "Expr: ";
    if(expr != nullptr)
        expr->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> While::infer() {
    auto condition_type = this->condition->infer();
    auto expr_type = this->expr->infer();        
    
    st->add_constraint(condition_type, std::make_shared<TypeVariable>(TypeTag::Bool), this->lineno);
    st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Unit), this->lineno);

    return this->type_variable;
}

void While::sem() {
    this->condition->sem();
    this->expr->sem();        
}

llvm::Value* While::codegen() { 
    auto current_function = Builder.GetInsertBlock()->getParent();

    //Create BB for the loop
    auto loop_start_BB = llvm::BasicBlock::Create(TheContext, "loop_start", current_function);
    auto loop_body_BB = llvm::BasicBlock::Create(TheContext, "loop_body");
    auto loop_end_BB = llvm::BasicBlock::Create(TheContext, "loop_end");

    //Enter the loop
    Builder.CreateBr(loop_start_BB);
    Builder.SetInsertPoint(loop_start_BB);

    auto condition_value = this->condition->codegen();

    Builder.CreateCondBr(condition_value, loop_body_BB, loop_end_BB);

    //Start loop body BB
    current_function->getBasicBlockList().push_back(loop_body_BB);
    Builder.SetInsertPoint(loop_body_BB);

    this->expr->codegen();

    loop_body_BB = Builder.GetInsertBlock();
    Builder.CreateBr(loop_start_BB);

    //end of loop
    current_function->getBasicBlockList().push_back(loop_end_BB);
    Builder.SetInsertPoint(loop_end_BB);

    return llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { });
}