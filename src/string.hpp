#ifndef __STRING_HPP__
#define __STRING_HPP__

#include "enums.hpp"
#include "expr.hpp"
#include <iostream>
#include <vector>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

class String : public Expr{
public:
    String(std::string* value);
    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;
    
    virtual llvm::Value* codegen();

private:
    std::string value;    
};

#endif