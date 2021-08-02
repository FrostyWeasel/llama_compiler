#ifndef __BINOP_HPP__
#define __BINOP_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include <iostream>
#include <vector>
#include <memory>

class TypeVariable;

class BinOp : public Expr {
public:

    BinOp(Expr* lval, Expr* rval, OpType op);

    virtual ~BinOp();

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer();

    virtual void sem() override;

    virtual llvm::Value* codegen();

private:
    Expr* lval;
    Expr* rval;
    OpType op;
};

#endif