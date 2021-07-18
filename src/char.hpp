#ifndef __CHAR_HPP__
#define __CHAR_HPP__

#include <iostream>
#include "type_variable.hpp"
#include "enums.hpp"
#include "expr.hpp"

class Char : public Expr{
public:
    Char(char value): value(value), Expr(new TypeVariable(TypeTag::Char)) { }
    virtual void print(std::ostream& out) const override {
        out << value;
    }

    virtual std::shared_ptr<TypeVariable> infer() override { 
        return this->type_variable;
    }

    virtual void sem() override { /* No need for further checks */ }

private:
    char value;
    
};

#endif