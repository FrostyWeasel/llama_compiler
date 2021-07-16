#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>
#include "enums.hpp"
#include "expr.hpp"
#include "type_variable.hpp"

class String : public Expr{
public:
    String(std::string* value): value(*value), Expr(new TypeVariable(TypeTag::Array, new TypeVariable(TypeTag::Char))) {  }
    virtual void print(std::ostream& out) const override{
        out << "String(";
        out << " Value: " << value;
        out << ") ";
    }

    virtual TypeVariable* infer() override { 
        return this->type_variable;
    }

private:
    std::string value;    
};

#endif