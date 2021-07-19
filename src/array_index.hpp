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

    ~ArrayIndex() {
        delete expr_list;
    }

    virtual void print(std::ostream &out) const override{
        out << "ArrayIndex( ";
        out << "Id: " << id << ", ";
        out << "Expr_list: ";
        if(expr_list != nullptr)
            expr_list->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        SymbolEntry* entry = st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);        

        //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
        this->expr_list->infer();

        auto array_element_type = std::make_shared<TypeVariable>();

        this->type_variable = std::make_shared<TypeVariable>(TypeTag::Reference, array_element_type);

        st->add_constraint(entry->get_type(), std::make_shared<TypeVariable>(TypeTag::Array,
            array_element_type, this->expr_list->block_size(), DimType::Exact));

        return this->type_variable;
    }

    virtual void sem() override {

        //All expressions in the expression comma list must be of type int and their count is the dimension of the array.
        this->expr_list->sem();
    }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif