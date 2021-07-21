#ifndef __INT_HPP__
#define __INT_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"


class Int : public Expr{
public:
    Int(int value) : value(value), Expr(new TypeVariable(TypeTag::Int)) { }
    virtual void print(std::ostream& out) const override{
        out << value;
    }

    virtual std::shared_ptr<TypeVariable> infer() override { 
        return this->type_variable;
    }

    virtual void sem() override { /* No need for further checks */ }

    virtual llvm::Value* codegen() const {
        return c32(this->value);
    }

private:
    int value;    
};

#endif