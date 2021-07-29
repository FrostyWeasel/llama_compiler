#ifndef __WHILE_HPP__
#define __WHILE_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include <memory>
#include <iostream>

class While : public Expr{
public:
    While(Expr* condition, Expr* expr): condition(condition), expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}

    virtual ~While() {
        delete condition;
        delete expr;
    }

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Expr* condition;
    Expr* expr;

};

#endif