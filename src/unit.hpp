#ifndef __UNIT_HPP__
#define __UNIT_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include "type.hpp"
#include <iostream>

class Unit : public Expr{
public:
    Unit() : Expr(new Type(TypeTag::Unit, this)) { }

    virtual void print(std::ostream& out) const override{
        out << "Unit";
    }  

    virtual Type* infer() override { 
        return this->type;
    }  

};

#endif