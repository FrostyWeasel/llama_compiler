#ifndef __FORTO_HPP__
#define __FORTO_HPP__

#include "for.hpp"

class ForTo : public For{
public:
    ForTo(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr): For(id, first_condition, second_condition, expr) {}

};

#endif