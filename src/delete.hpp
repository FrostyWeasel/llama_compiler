#ifndef __DELETE_HPP__
#define __DELETE_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include <memory>
#include <iostream>

class Delete : public Expr{
public:
    Delete(Expr* expr): expr(expr), Expr(new TypeVariable(TypeTag::Unit)) {}
    virtual ~Delete()  {}

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Expr* expr;
};

#endif