#ifndef __LETDEF_HPP__
#define __LETDEF_HPP__

#include "ast.hpp"
#include "includes.hpp"

//TODO: Put def in symboltable with recursive letdefs allowing expr in defs to use the id just defined.
class LetDef : public AST{
public:    
    LetDef(Block<Def>* def, LetType type): def(def), type(type) {}
  
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

private:
    Block<Def>* def;
    LetType type;
};

#endif
