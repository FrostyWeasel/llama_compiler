#ifndef __ARRAYINDEX_HPP__
#define __ARRAYINDEX_HPP__

#include "enums.hpp"
#include "expr.hpp"
#include <memory>
#include <string>
#include <iostream>

class TypeVariable;

template <class T>
class Block;
class ArrayIndex : public Expr{
public:
    ArrayIndex(std::string* id, Block<Expr>* expr_list);

    virtual ~ArrayIndex();

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif