#ifndef __IF_HPP__
#define __IF_HPP__

#include "expr.hpp"
#include "enums.hpp"
#include "type_variable.hpp"


class If : public Expr{
public:
    If(Expr* condition, Expr* if_expr): condition(condition), if_expr(if_expr), else_expr(nullptr), Expr(new TypeVariable(TypeTag::Unit)) {}
    If(Expr* condition, Expr* if_expr, Expr* else_expr): condition(condition), if_expr(if_expr), else_expr(else_expr), Expr(new TypeVariable()) {}

    virtual ~If() {
        delete condition;
        delete if_expr;
        delete else_expr;
    }

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Expr* condition;
    Expr* if_expr;
    Expr* else_expr;

};

#endif