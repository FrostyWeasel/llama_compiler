#ifndef __LETDEF_HPP__
#define __LETDEF_HPP__

// #include "global_variables.hpp"
#include "ast.hpp"
#include "def.hpp"
#include "block.hpp"
#include "enums.hpp"
#include "symbol_table.hpp"

//TODO: After sem check that : let x = 5 let rec x = x + 6 does not work but let x = 5 let x = x + 5 does

class LetDef : public AST{
public:    
    LetDef(Block<Def>* def, LetType let_type): def(def), let_type(let_type) {}

    virtual ~LetDef() {
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

    virtual std::shared_ptr<TypeVariable> infer() override {
        AST::st->scope_open();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(true);
        
        //The definitions are first added to the symboltable and then type inference and semantic analysis happens
        //This is to allow mutually recursive definitions ex.let rec even n = if n=0 then true else odd (n-1) and odd n = if n=0 then false else even (n-1)
        this->def->add_to_symbol_table();

        std::shared_ptr<TypeVariable> type = def->infer();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(false);

        return type;
    }

    virtual void sem() override {     
        AST::st->scope_open();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(true);
        
        //The definitions are first added to the symboltable and then type inference and semantic analysis happens
        //This is to allow mutually recursive definitions ex.let rec even n = if n=0 then true else odd (n-1) and odd n = if n=0 then false else even (n-1)
        this->def->add_to_symbol_table();

        def->sem();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(false);
    };

    virtual llvm::Value* codegen() const override {
        AST::st->scope_open();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(true);
        
        //The definitions are first added to the symboltable and then type inference and semantic analysis happens
        //This is to allow mutually recursive definitions ex.let rec even n = if n=0 then true else odd (n-1) and odd n = if n=0 then false else even (n-1)
        this->def->add_to_symbol_table();

        auto def_value = def->codegen();

        if(let_type == LetType::NoRec)
            AST::st->scope_hide(false);

        return def_value;
    }

private:
    Block<Def>* def;
    LetType let_type;
};

#endif
