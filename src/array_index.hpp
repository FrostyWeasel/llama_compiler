#ifndef __ARRAYINDEX_HPP__
#define __ARRAYINDEX_HPP__

#include "expr.hpp"
#include "includes.hpp"


class ArrayIndex : public Expr{
public:
    ArrayIndex(std::string* id, Block<Expr>* expr_list) {}

};

#endif