#ifndef __ARRAYDEF_HPP__
#define __ARRAYDEF_HPP__

#include "type_variable.hpp"
#include "enums.hpp"
#include "block.hpp"
#include "def.hpp"
#include "expr.hpp"
#include "variable_entry.hpp"
#include <iostream>
#include <string>
#include <vector>

class ArrayDef : public Def {
public:
    ArrayDef(std::string* id, Block<Expr>* expr_list): id(*id), Def(new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Unknown), expr_list->block_size(), DimType::Exact)), expr_list(expr_list) {}
    ArrayDef(std::string* id, Block<Expr>* expr_list, std::shared_ptr<TypeVariable> type_variable): id(*id), expr_list(expr_list), Def(new TypeVariable(TypeTag::Array, type_variable, expr_list->block_size(), DimType::Exact)) {}

    virtual ~ArrayDef() {
        delete expr_list;
    }

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