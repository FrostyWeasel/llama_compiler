#ifndef __LETIN_HPP__
#define __LETIN_HPP__

#include "expr.hpp"
#include "let_def.hpp"
#include "type_variable.hpp"
#include<iostream>

//TODO: Open new scope for expression
class LetIn : public Expr{
public:
    LetIn(LetDef* let_def, Expr* expr): let_def(let_def), expr(expr) {}

    ~LetIn() {
        delete expr;
        delete let_def;
    }

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

    virtual std::shared_ptr<TypeVariable> infer() override {
        //Opens but does not close scope.
        //* Let def type thrown away.
        this->let_def->infer(); 

        this->type_variable = this->expr->infer();

        //Letdef scope only encompasses expression.
        st->scope_close();

        return this->type_variable;
    }

private:
    LetDef* let_def;
    Expr* expr;

};

#endif