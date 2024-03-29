#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "ast.hpp"
#include "enums.hpp"
#include <memory>

class SymbolEntry;
class TypeVariable;

class Expr : public AST{
public:  
    Expr();
    Expr(TypeVariable* type_variable);

    virtual ~Expr() {}

    virtual void print(std::ostream &out) const override = 0;

    virtual void set_type(std::shared_ptr<TypeVariable> type_variable) { this->type_variable = type_variable; }

    virtual std::shared_ptr<TypeVariable> get_type() { return this->type_variable; }

    virtual SymbolEntry* get_entry() { return this->entry; }

    virtual std::string get_id() override { return ""; };


protected:
    std::shared_ptr<TypeVariable> type_variable;
    SymbolEntry* entry; 
};

#endif