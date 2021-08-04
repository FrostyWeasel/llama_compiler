#ifndef __FOR_HPP__
#define __FOR_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include <memory>
#include <string>
#include <iostream>

class TypeVariable;
class For : public Expr {
public:
    For();
    For(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr);

    virtual ~For();

    virtual void print(std::ostream &out) const override = 0;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override = 0;

    virtual std::string get_id() override { return this->id; }

protected:
    std::string id;
    Expr* first_condition;
    Expr* second_condition;
    Expr* expr;

};

#endif