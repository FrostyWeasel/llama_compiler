#ifndef __DEF_HPP__
#define __DEF_HPP__

#include "ast.hpp"
#include "includes.hpp"

class Def : public AST{
public:    
    Def(std::string* id, Block<Par>* par_list, Type* type, Expr* expr) {}
    Def(std::string* id, Block<Par>* par_list, Expr* expr) {}
    Def(std::string* id, Block<Expr>* expr_list) {}
    Def(std::string* id, Block<Expr>* expr_list, Type* type) {}
    Def(std::string* id) {}

    virtual void print(std::ostream &out) const override {}

};

#endif