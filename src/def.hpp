#ifndef __DEF_HPP__
#define __DEF_HPP__

#include <iostream>
#include "ast.hpp"
#include "enums.hpp"
#include "type_variable.hpp"
#include "symbol_entry.hpp"
#include <string>
#include <memory>

class Def : public AST {
public:    
    Def() : AST(NodeType::Def) {}
    Def(TypeVariable* type_variable) : type_variable(std::make_shared<TypeVariable>(*type_variable)), AST(NodeType::Def) { }
    Def(std::shared_ptr<TypeVariable> type_variable) : type_variable(type_variable), AST(NodeType::Def) { }

    virtual ~Def()  {}

    virtual void set_type( std::shared_ptr<TypeVariable> type_variable) { this->type_variable = type_variable; }

protected:
    std::shared_ptr<TypeVariable> type_variable;
    //The entry in the ST corresponding to this definition 
    //* Do not delete this it is owned by the ST.
    SymbolEntry* entry; 
};

#endif