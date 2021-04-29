#ifndef __LETIN_HPP__
#define __LETIN_HPP__

#include "expr.hpp"
#include "includes.hpp"


class LetIn : public Expr{
public:
    LetIn(LetDef* let_def, Expr* expr) {}

};

#endif