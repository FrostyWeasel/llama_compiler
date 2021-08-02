#ifndef __NEW_HPP__
#define __NEW_HPP__

#include "expr.hpp"
#include "enums.hpp"

class TypeVariable;

class New : public Expr{
public:
    New(std::shared_ptr<TypeVariable> type_variable);

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    std::shared_ptr<TypeVariable> new_type_variable;
};

#endif