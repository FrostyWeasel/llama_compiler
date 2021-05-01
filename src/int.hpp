#ifndef __INT_HPP__
#define __INT_HPP__

#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "includes.hpp"


class Int : public Expr{
public:
    Int(int value) : value(value), type(new Type(TypeTag::Int)) {}
    virtual void print(std::ostream& out) const override{
        out << "Int(" << value << ") ";
    }

private:
    int value;
    Type* type;
};

#endif