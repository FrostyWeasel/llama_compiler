#ifndef __BOOL_HPP__
#define __BOOL_HPP__

#include "expr.hpp"
#include "includes.hpp"
class Bool : public Expr{
public:
    Bool(bool value) : value(value), Expr(new Type(TypeTag::Bool)) {}

    virtual void print(std::ostream& out) const override{
        out << "Bool(" << value << ") ";
    }
    
private:
    bool value;
    

};

#endif