#include "if.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <iostream>

If::If(Expr* condition, Expr* if_expr): condition(condition), if_expr(if_expr), else_expr(nullptr), Expr(new TypeVariable(TypeTag::Unit)) {}
If::If(Expr* condition, Expr* if_expr, Expr* else_expr): condition(condition), if_expr(if_expr), else_expr(else_expr), Expr(new TypeVariable()) {}

void If::print(std::ostream &out) const {
        out << "If(";
        out << "Type: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << "Condition: ";
        if(condition != nullptr)
            condition->print(out);
        else
            out << "null ";
        out << "If_Expr: ";
        if(if_expr != nullptr)
            if_expr->print(out);
        else
            out << "null ";
        out << "Else_Expr: ";
        if(else_expr != nullptr)
            else_expr->print(out);
        else
            out << "null ";
        out << ") ";
    }

std::shared_ptr<TypeVariable> If::infer() {
    auto if_expr_type = this->if_expr->infer();
    
    if (else_expr != nullptr) {
        auto else_expr_type = this->else_expr->infer();

        st->add_constraint(if_expr_type, else_expr_type, this->lineno);
    }
    else {
        st->add_constraint(if_expr_type, std::make_shared<TypeVariable>(TypeTag::Unit), this->lineno);
    }

    auto condition_type = this->condition->infer();

    st->add_constraint(condition_type, std::make_shared<TypeVariable>(TypeTag::Bool), this->lineno);
    st->add_constraint(this->type_variable, if_expr_type, this->lineno);

    return if_expr_type;
}

void If::sem() {
    this->if_expr->sem();
    
    if (else_expr != nullptr) {
        this->else_expr->sem();
    }

    this->condition->sem();
}

llvm::Value* If::codegen() {
    auto condition_value = this->condition->codegen();
    auto condition_result = Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, condition_value, c1(1));

    auto current_function = Builder.GetInsertBlock()->getParent();

    if(this->else_expr == nullptr) {
        auto then_BB = llvm::BasicBlock::Create(TheContext, "then", current_function);
        auto if_end_BB = llvm::BasicBlock::Create(TheContext, "endif");

        Builder.CreateCondBr(condition_result, then_BB, if_end_BB);

        //Generate code for the then clause
        Builder.SetInsertPoint(then_BB);
        this->if_expr->codegen();
        Builder.CreateBr(if_end_BB);

        //Codegen for the then block can change the basic block but it is needed for the phi expression
        then_BB = Builder.GetInsertBlock();

        current_function->getBasicBlockList().push_back(if_end_BB);
        Builder.SetInsertPoint(if_end_BB);

        return llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { });
    }
    else {
        auto then_BB = llvm::BasicBlock::Create(TheContext, "then", current_function);
        auto else_BB = llvm::BasicBlock::Create(TheContext, "else");
        auto if_end_BB = llvm::BasicBlock::Create(TheContext, "endif");

        Builder.CreateCondBr(condition_result, then_BB, else_BB);

        //Generate code for the then clause
        Builder.SetInsertPoint(then_BB);
        auto then_value = this->if_expr->codegen();
        Builder.CreateBr(if_end_BB);

        //Codegen for the then block can change the basic block but it is needed for the phi expression
        then_BB = Builder.GetInsertBlock();

        //A bunch of new basic blocks could have been inserted by the then expression above, now we also add the else BB after them
        current_function->getBasicBlockList().push_back(else_BB);
        Builder.SetInsertPoint(else_BB);

        //Generate code for the else clause
        auto else_value = this->else_expr->codegen();
        Builder.CreateBr(if_end_BB);
        else_BB = Builder.GetInsertBlock();

        current_function->getBasicBlockList().push_back(if_end_BB);
        Builder.SetInsertPoint(if_end_BB);

        auto phi_node = Builder.CreatePHI(map_to_llvm_type(this->type_variable), 2, "iftmp");
        phi_node->addIncoming(then_value, then_BB);
        phi_node->addIncoming(else_value, else_BB);

        return phi_node;
    }
}