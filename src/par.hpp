#ifndef __PAR_HPP__
#define __PAR_HPP__

#include "ast.hpp"
#include "includes.hpp"

class Par : public AST{
public:
    Par(std::string* id) {}
    Par(std::string* id, Type* type) {}
    virtual void print(std::ostream &out) const override {  }

};

#endif