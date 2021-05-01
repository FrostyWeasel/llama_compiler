#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>
#include "enums.hpp"
#include "expr.hpp"
#include "includes.hpp"

class String : public Expr{
public:
    String(std::string* value): value(*value), type(new ArrayType(new Type(TypeTag::Char))) {  }
    virtual void print(std::ostream& out) const override{
        out << "String(";
        out << " Value: " << value;
        out << ") ";
    }

private:
    std::string value;
    Type* type;
};

#endif