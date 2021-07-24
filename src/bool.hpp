#ifndef __BOOL_HPP__
#define __BOOL_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
class Bool : public Expr{
public:
    Bool(bool value) : value(value), Expr(new TypeVariable(TypeTag::Bool)) {}

    virtual void print(std::ostream& out) const override{
        out << value;
    }

    virtual std::shared_ptr<TypeVariable> infer() override { 
        return this->type_variable;
    }

    virtual void sem() override { /* No need for further checks */ }
    
    virtual llvm::Value* codegen() {
        return c1(this->value);
    }

private:
    bool value;
};

#endif