#ifndef __BINOP_HPP__
#define __BINOP_HPP__

#include "expr.hpp"
#include "includes.hpp"


class BinOp : public Expr{
public:
    BinOp(Expr* lval, Expr* rval, BinOpType) {}

};

#endif