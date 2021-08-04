#ifndef __DIM_HPP__
#define __DIM_HPP__

#include "expr.hpp"
#include <iostream>
#include <memory>
#include <string>

class Dim : public Expr{
public:
    Dim(std::string* id): id(*id), dimension(1) {}
    Dim(std::string* id, unsigned int dimension): id(*id), dimension(dimension) {}

    virtual void print(std::ostream &out) const override;
    virtual std::shared_ptr<TypeVariable> infer() override;
    virtual void sem() override;
    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
    unsigned int dimension;

};

#endif