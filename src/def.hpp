#ifndef __DEF_HPP__
#define __DEF_HPP__

#include <iostream>
#include <string>
#include "ast.hpp"
#include "enums.hpp"
#include "type_variable.hpp"

class Def : public AST {
public:    
    Def() : AST(NodeType::Def) {}
    Def(TypeVariable* type_variable) : type_variable(type_variable), AST(NodeType::Def) { }

    virtual ~Def() {
        delete type_variable;
    }

    virtual void set_type( TypeVariable* type_variable) { this->type_variable = type_variable; }

protected:
    TypeVariable* type_variable;
};

#endif