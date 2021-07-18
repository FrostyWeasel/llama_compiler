#ifndef __UNIT_HPP__
#define __UNIT_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include "type_variable.hpp"
#include <iostream>

class Unit : public Expr{
public:
    Unit() : Expr(new TypeVariable(TypeTag::Unit)) { }

    virtual void print(std::ostream& out) const override{
        out << "()";
    }  

    virtual std::shared_ptr<TypeVariable> infer() override { 
        return this->type_variable;
    }  

    virtual void sem() override { /* No need for further checks */ }

};

#endif