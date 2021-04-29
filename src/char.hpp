#ifndef __CHAR_HPP__
#define __CHAR_HPP__

#include <iostream>
#include "expr.hpp"
#include "includes.hpp"


class Char : public Expr{
public:
    Char(char value) { std::cout << "Char created with value:" << value << '\n'; }

};

#endif