#ifndef __FOR_HPP__
#define __FOR_HPP__

#include "expr.hpp"
#include "includes.hpp"


class For : public Expr{
public:
    For() {}
    For(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr) {}

};

#endif