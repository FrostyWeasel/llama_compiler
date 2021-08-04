#ifndef __ID_HPP__
#define __ID_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "enums.hpp"

class TypeVariable;

class Id : public Expr{
public:
    Id(std::string* id);

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
    
};

#endif