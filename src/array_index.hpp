#ifndef __ARRAYINDEX_HPP__
#define __ARRAYINDEX_HPP__

#include "expr.hpp"
#include "includes.hpp"

//TODO: TypeCheck: All expr in expr_list should be ints, should be: expr_list->size = id->type->dimensions.
//TODO: TypeInference: Result is a type = ref t where t is the type of array elements.

class ArrayIndex : public Expr{
public:
    ArrayIndex(std::string* id, Block<Expr>* expr_list): id(*id), expr_list(expr_list) {}

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

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif