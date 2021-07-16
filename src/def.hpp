#ifndef __DEF_HPP__
#define __DEF_HPP__

#include <iostream>
#include <string>
#include "ast.hpp"
#include "enums.hpp"
#include "type.hpp"

class Def : public AST {
public:    
    Def() :  AST(NodeType::Def) {}
    Def(Type* type) : type(type), AST(NodeType::Def) { type->set_parent(this); }

    virtual ~Def() {
        delete type;
    }

    virtual void set_type(Type* type) { this->type = type; }

protected:
    Type* type;
};

#endif