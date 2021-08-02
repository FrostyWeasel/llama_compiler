#ifndef __FLOAT_HPP__
#define __FLOAT_HPP__

#include "expr.hpp"
#include "enums.hpp"

class Float : public Expr{
public:
    Float(float value);
    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen();

private:
    double value;    
};

#endif