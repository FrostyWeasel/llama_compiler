#ifndef __INT_HPP__
#define __INT_HPP__

#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "includes.hpp"


class Int : public Expr{
public:
    Int(int value) : value(value), Expr(new Type(TypeTag::Int, this)) { }
    virtual void print(std::ostream& out) const override{
        out << "Int(" << value << ") ";
    }

    virtual Type* infer() override { 
        return this->type;
    }

private:
    int value;    
};

#endif