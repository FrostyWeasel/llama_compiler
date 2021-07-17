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

//TODO: TypeCheck: All expressions in expr_list should have type=int.
//TODO: TypeInference: Type is arraytype [*...expr_list->size] of type
//TODO: SymbolTable: Array[expr_list[0]][expr_list[1]]...

class ArrayDef : public Def {
public:
    ArrayDef(std::string* id, Block<Expr>* expr_list): id(*id), Def(new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Unknown), expr_list->block_size(), DimType::Exact)), expr_list(expr_list) {}
    ArrayDef(std::string* id, Block<Expr>* expr_list, std::shared_ptr<TypeVariable> type_variable): id(*id), expr_list(expr_list), Def(new TypeVariable(TypeTag::Array, type_variable, expr_list->block_size(), DimType::Exact)) {}

    ~ArrayDef() {
        delete expr_list;
    }

    virtual void print(std::ostream& out) const override{
        out << " mutable " << id << "[";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        if(expr_list != nullptr)
            expr_list->print(out);
        else
            out << "null ";
        out << "]";
    }

    virtual void add_to_symbol_table() override {
        VariableEntry* entry = new VariableEntry(id, EntryType::ENTRY_VARIABLE, this->type_variable, this->expr_list->block_size());
        
        st->insert_entry(entry);

        this->entry = entry;
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
        this->expr_list->infer();

        return this->type_variable;
    }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif