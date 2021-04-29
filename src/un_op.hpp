#ifndef __UNOP_HPP__
#define __UNOP_HPP__

#include "expr.hpp"
#include "includes.hpp"


class UnOp : public Expr{
public:
    UnOp(Expr* expr, UnOpType type) {}

};

#endif