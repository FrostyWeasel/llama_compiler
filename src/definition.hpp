#ifndef __DEFINITION_HPP__
#define __DEFINITION_HPP__

#include "ast.hpp"

class Definition : public AST {
public:
    Definition() = default;

    virtual ~Definition() = default;

    virtual void print(std::ostream &out) const override = 0;

    virtual std::shared_ptr<TypeVariable> infer() override = 0;

    virtual void sem() override = 0;

    virtual llvm::Value* codegen() override = 0;

};

#endif