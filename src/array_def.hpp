#ifndef __ARRAYDEF_HPP__
#define __ARRAYDEF_HPP__

#include "def.hpp"
#include "enums.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Expr;
class TypeVariable;

template <class T>
class Block;

class ArrayDef : public Def {
public:
    ArrayDef(std::string* id, Block<Expr>* expr_list);
    ArrayDef(std::string* id, Block<Expr>* expr_list, std::shared_ptr<TypeVariable> type_variable);

    virtual ~ArrayDef();

    virtual void print(std::ostream &out) const override;

    virtual void add_to_symbol_table() override;

    virtual void allocate() override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;


    virtual llvm::Value* codegen() override;

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif