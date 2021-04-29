#ifndef __FUNCTIONCALL_HPP__
#define __FUNCTIONCALL_HPP__

#include "expr.hpp"
#include "includes.hpp"


class FunctionCall : public Expr{
public:
    FunctionCall(std::string* id, Block<Expr>* expr_list) {}

};

#endif