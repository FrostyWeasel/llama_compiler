#ifndef __LETDEF_HPP__
#define __LETDEF_HPP__

// #include "global_variables.hpp"
#include "ast.hpp"
#include "def.hpp"
#include "block.hpp"
#include "enums.hpp"
#include "symbol_table.hpp"

//TODO: After sem check that : let x = 5 let rec x = x + 6 does not work but let x = 5 let x = x + 5 does
//TODO: Check that you can run infer without opening scopes (you propably cant)
class LetDef : public AST{
public:    
    LetDef(Block<Def>* def, LetType let_type): def(def), let_type(let_type) {}

    ~LetDef() {
        delete def;
    }
  
    virtual void print(std::ostream &out) const override {
        out << "Let(";
        out << "Type: " << ((let_type == LetType::Rec) ? "Rec" : "NonRec") << ", ";
        out << "Def: ";
        if(def != nullptr)
            def->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual TypeVariable* infer() override {
        AST::st->scope_open();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(true);
        
        //TODO:Is the current scope always the same as the one just hidden upon return?
        TypeVariable* type = def->infer();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(false);

        return type;
    }

    virtual void sem() override {     
        AST::st->scope_open();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(true);
        
        def->sem();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(false);
    };

private:
    Block<Def>* def;
    LetType let_type;
};

#endif
