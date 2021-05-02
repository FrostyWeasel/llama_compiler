#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "ast.hpp"

class Expr : public AST{
public:  
    Expr() {}
    Expr(Type* type): type(type) {}

    virtual ~Expr(){
        delete type;
    }

    virtual void print(std::ostream &out) const override = 0;

protected:
    Type* type;
};

#endif