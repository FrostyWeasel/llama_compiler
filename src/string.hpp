#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>
#include "enums.hpp"
#include "expr.hpp"
#include "type_variable.hpp"

class String : public Expr{
public:
    String(std::string* value): value(*value), Expr(new TypeVariable(TypeTag::Array, std::make_shared<TypeVariable>(TypeTag::Char))) {  }
    virtual void print(std::ostream& out) const override{
        out << value;
    }

    virtual std::shared_ptr<TypeVariable> infer() override { 
        return this->type_variable;
    }

    virtual void sem() override { /* No need for further checks */ }

private:
    std::string value;    
};

#endif