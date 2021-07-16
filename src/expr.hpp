#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "ast.hpp"
#include "enums.hpp"
#include "type_variable.hpp"

class Expr : public AST{
public:  
    Expr() : AST(NodeType::Expr) {}
    Expr(TypeVariable* type_variable): type_variable(type_variable), AST(NodeType::Expr) { }

    virtual ~Expr(){
        delete type_variable;
    }

    virtual void print(std::ostream &out) const override = 0;

    virtual void set_type(TypeVariable* type_variable) { this->type_variable = type_variable; }

protected:
    TypeVariable* type_variable;
};

#endif