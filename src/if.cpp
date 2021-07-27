#include "if.hpp"

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

        st->add_constraint(if_expr_type, else_expr_type);
    }
    else {
        st->add_constraint(if_expr_type, std::make_shared<TypeVariable>(TypeTag::Unit));
    }

    auto condition_type = this->condition->infer();

    st->add_constraint(condition_type, std::make_shared<TypeVariable>(TypeTag::Bool));
    st->add_constraint(this->type_variable, if_expr_type);

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

    auto current_fuction = Builder.GetInsertBlock()->getParent();

    auto then_BB = llvm::BasicBlock::Create(TheContext, "then", current_fuction);
    auto else_BB = llvm::BasicBlock::Create(TheContext, "else", current_fuction);
    auto if_end_BB = llvm::BasicBlock::Create(TheContext, "endif", current_fuction);
}