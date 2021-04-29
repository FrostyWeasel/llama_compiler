#ifndef __IF_HPP__
#define __IF_HPP__

#include "expr.hpp"
#include "includes.hpp"


class If : public Expr{
public:
    If(Expr* condition, Expr* expr) {}
    If(Expr* condition, Expr* if_expr, Expr* else_expr) {}

};

#endif