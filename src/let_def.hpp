#ifndef __LETDEF_HPP__
#define __LETDEF_HPP__

// #include "global_variables.hpp"
#include "ast.hpp"
#include "def.hpp"
#include "block.hpp"
#include "enums.hpp"
#include "symbol_table.hpp"

extern SymbolTable* st;

//TODO: Put def in symboltable with recursive letdefs allowing expr in defs to use the id just defined.
class LetDef : public AST{
public:    
    LetDef(Block<Def>* def, LetType type): def(def), type(type) {}

    ~LetDef() {
        delete def;
    }
  
    virtual void print(std::ostream &out) const override {
        out << "Let(";
        out << "Type: " << ((type == LetType::Rec) ? "Rec" : "NonRec") << ", ";
        out << "Def: ";
        if(def != nullptr)
            def->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual void sem() override {     
        st->scope_open(); 
    };

private:
    Block<Def>* def;
    LetType type;
};

#endif
