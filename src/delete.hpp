#ifndef __DELETE_HPP__
#define __DELETE_HPP__

#include "expr.hpp"
#include <memory>
#include <iostream>

class TypeVariable;

class Delete : public Expr{
public:
    Delete(Expr* expr);
    virtual ~Delete();

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Expr* expr;
};

#endif