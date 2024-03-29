#ifndef __INT_HPP__
#define __INT_HPP__

#include "expr.hpp"
#include "enums.hpp"


class Int : public Expr{
public:
    Int(int value);
    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen();

private:
    int value;    
};

#endif