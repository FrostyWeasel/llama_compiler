#ifndef __LETIN_HPP__
#define __LETIN_HPP__

#include "expr.hpp"
#include "includes.hpp"

//TODO: Open new scope for expression
class LetIn : public Expr{
public:
    LetIn(LetDef* let_def, Expr* expr): let_def(let_def), expr(expr) {}

    virtual void print(std::ostream &out) const override {
        out << "LetIn(";
        out << "LetDef: ";
        if(let_def != nullptr)
            let_def->print(out);
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
    LetDef* let_def;
    Expr* expr;

};

#endif