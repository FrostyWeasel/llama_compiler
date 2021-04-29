#ifndef __DIM_HPP__
#define __DIM_HPP__

#include "expr.hpp"
#include "includes.hpp"


class Dim : public Expr{
public:
    Dim(std::string* id) {}
    Dim(std::string* id, int dimension) {}

};

#endif