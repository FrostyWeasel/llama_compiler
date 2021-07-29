#ifndef __FOR_HPP__
#define __FOR_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "constant_entry.hpp"
#include "enums.hpp"
#include <memory>
#include <string>
#include <iostream>

class For : public Expr {
public:
    For() {}
    For(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr): id(*id), first_condition(first_condition), second_condition(second_condition), expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}

    virtual ~For() {
        delete first_condition;
        delete second_condition;
        delete expr;
    }

    virtual void print(std::ostream &out) const override = 0;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override = 0;

protected:
    std::string id;
    Expr* first_condition;
    Expr* second_condition;
    Expr* expr;

};

#endif