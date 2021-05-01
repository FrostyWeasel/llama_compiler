#ifndef __UNIT_HPP__
#define __UNIT_HPP__

#include "expr.hpp"
#include "includes.hpp"


class Unit : public Expr{
public:
    Unit() : type(new Type(TypeTag::Unit)) {}

    virtual void print(std::ostream& out) const override{
        out << "Unit";
    }

private:
    Type* type;

};

#endif