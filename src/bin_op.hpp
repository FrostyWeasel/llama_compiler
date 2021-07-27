#ifndef __BINOP_HPP__
#define __BINOP_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include <iostream>
#include <vector>

class BinOp : public Expr {
public:

    BinOp(Expr* lval, Expr* rval, OpType op): lval(lval), rval(rval), op(op) {}

    virtual ~BinOp() {
        delete lval;
        delete rval;
    }

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