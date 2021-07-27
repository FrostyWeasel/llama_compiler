#ifndef __LETIN_HPP__
#define __LETIN_HPP__

#include "expr.hpp"
#include "let_def.hpp"
#include "type_variable.hpp"
#include<iostream>

class LetIn : public Expr{
public:
    LetIn(LetDef* let_def, Expr* expr): let_def(let_def), expr(expr) {}

    virtual ~LetIn() {
        delete expr;
        delete let_def;
    }

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    LetDef* let_def;
    Expr* expr;

    // * In case that a function is defined in let def then the static current_func_def_non_locals will point to the new function
    // * after the return of the definition we should append all variables found in the local definition to the non locals of the parent function
    std::map<std::string, std::shared_ptr<TypeVariable>>* parent_function_non_locals = nullptr;

};

#endif