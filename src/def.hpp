#ifndef __DEF_HPP__
#define __DEF_HPP__

#include "ast.hpp"
#include "enums.hpp"
#include <string>
#include <memory>
#include <iostream>

class SymbolEntry;
class TypeVariable;

class Def : public AST {
public:    
    Def();
    Def(TypeVariable* type_variable);
    Def(std::shared_ptr<TypeVariable> type_variable);

    virtual ~Def()  {}

    virtual void set_type( std::shared_ptr<TypeVariable> type_variable) { this->type_variable = type_variable; }
    virtual std::shared_ptr<TypeVariable> get_type() { return this->type_variable; }

    virtual SymbolEntry* get_entry() { return this->entry; }

    virtual std::string get_id() override = 0;

protected:
    std::shared_ptr<TypeVariable> type_variable;
    //The entry in the ST corresponding to this definition 
    //* Do not delete this it is owned by the ST.
    SymbolEntry* entry; 
};

#endif