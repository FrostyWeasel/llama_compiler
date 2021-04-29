#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include "ast.hpp"
#include "includes.hpp"


class Type : public AST{
public:public:
    Type() {}
    Type(TypeTag type) {}
    virtual void print(std::ostream &out) const override {  }
};

#endif