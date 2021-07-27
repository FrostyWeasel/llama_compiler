#ifndef __ID_HPP__
#define __ID_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "symbol_entry.hpp"
#include "constant_entry.hpp"
#include "parameter_entry.hpp"

class Id : public Expr{
public:
    Id(std::string* id): id(*id) {}

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    std::string id;
    
};

#endif