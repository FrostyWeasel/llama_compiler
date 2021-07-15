#ifndef __CHAR_HPP__
#define __CHAR_HPP__

#include <iostream>
#include "type.hpp"
#include "enums.hpp"
#include "expr.hpp"
#include "includes.hpp"

class Char : public Expr{
public:
    Char(char value): value(value), Expr(new Type(TypeTag::Char, this)) { }
    virtual void print(std::ostream& out) const override{
        out << "Char(" << value << ") ";
    }

    virtual Type* infer() override { 
        return this->type;
    }

private:
    char value;
    
};

#endif