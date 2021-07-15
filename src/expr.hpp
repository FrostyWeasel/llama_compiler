#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "ast.hpp"
#include "enums.hpp"

class Expr : public AST{
public:  
    Expr() : AST(NodeType::Expr) {}
    Expr(Type* type): type(type), AST(NodeType::Expr) { type->set_parent(this); }

    virtual ~Expr(){
        delete type;
    }

    virtual void print(std::ostream &out) const override = 0;

    virtual void set_type(Type* type) { this->type = type; }

protected:
    Type* type;
};

#endif