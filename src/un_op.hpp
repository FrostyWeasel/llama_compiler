#ifndef __UNOP_HPP__
#define __UNOP_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include <iostream>
#include <memory>

class TypeVariable;
class UnOp : public Expr{
public:
    UnOp(Expr* expr, OpType op);

    virtual ~UnOp();

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer();

    virtual void sem() override;

    virtual llvm::Value* codegen();

private:
    Expr* expr;
    OpType op;
};

#endif