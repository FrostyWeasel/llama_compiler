#ifndef __FORTO_HPP__
#define __FORTO_HPP__

#include "for.hpp"
#include <iostream>

class ForTo : public For {
public:
    ForTo(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr): For(id, first_condition, second_condition, expr) {}

    virtual void print(std::ostream &out) const override;

    virtual llvm::Value* codegen() override;

};

#endif