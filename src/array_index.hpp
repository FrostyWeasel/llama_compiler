#ifndef __ARRAYINDEX_HPP__
#define __ARRAYINDEX_HPP__

#include "expr.hpp"
#include "block.hpp"
#include "variable_entry.hpp"
#include "enums.hpp"
#include <memory>
#include <string>
#include <iostream>

class ArrayIndex : public Expr{
public:
    ArrayIndex(std::string* id, Block<Expr>* expr_list): id(*id), expr_list(expr_list) {}

    virtual ~ArrayIndex() {
        delete expr_list;
    }

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif