#ifndef __IF_HPP__
#define __IF_HPP__

#include "expr.hpp"
#include "includes.hpp"


class If : public Expr{
public:
    If(Expr* condition, Expr* if_expr): condition(condition), if_expr(if_expr), else_expr(nullptr) {}
    If(Expr* condition, Expr* if_expr, Expr* else_expr): condition(condition), if_expr(if_expr), else_expr(else_expr) {}

    ~If() {
	std::cout << "If deleted\n";
        delete condition;
        delete if_expr;
        delete else_expr;
    }

    virtual void print(std::ostream &out) const override {
        out << "If(";
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

    virtual Type* infer() override {
        auto if_expr_type = this->if_expr->infer();
        
        if (else_expr != nullptr) {
            auto else_expr_type = this->else_expr->infer();

            st->add_constraint(if_expr_type, else_expr_type);
        }

        auto condition_type = this->condition->infer();
        st->add_constraint(condition_type, new Type(TypeTag::Bool));

        return if_expr_type;
    }

private:
    Expr* condition;
    Expr* if_expr;
    Expr* else_expr;

};

#endif