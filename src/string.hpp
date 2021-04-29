#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>
#include "expr.hpp"
#include "includes.hpp"

class String : public Expr{
public:
    String(std::string* value) { std::cout << "String created with value: " << *value << '\n'; }

};

#endif