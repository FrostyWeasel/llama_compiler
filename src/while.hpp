#ifndef __WHILE_HPP__
#define __WHILE_HPP__

#include "expr.hpp"
#include "includes.hpp"


class While : public Expr{
public:
    While(Expr* condition, Expr* expr): condition(condition), expr(expr) {}

    virtual void print(std::ostream &out) const override {
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

private:
    Expr* condition;
    Expr* expr;

};

#endif