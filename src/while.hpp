#ifndef __WHILE_HPP__
#define __WHILE_HPP__

#include "expr.hpp"
#include "includes.hpp"


class While : public Expr{
public:
    While(Expr* condition, Expr* expr) {}

};

#endif