#ifndef __BOOL_HPP__
#define __BOOL_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
class Bool : public Expr{
public:
    Bool(bool value) : value(value), Expr(new TypeVariable(TypeTag::Bool)) {}

    virtual void print(std::ostream& out) const override{
        out << "Bool(" << value << ") ";
    }

    virtual TypeVariable* infer() override { 
        return this->type_variable;
    }
    
private:
    bool value;
    

};

#endif