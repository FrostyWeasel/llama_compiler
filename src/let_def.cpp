#include "let_def.hpp"

void LetDef::print(std::ostream &out) const {
    out << "Let(";
    out << "Type: " << ((let_type == LetType::Rec) ? "Rec" : "NonRec") << ", ";
    out << "Def: ";
    if(def != nullptr)
        def->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> LetDef::infer() {
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

void LetDef::sem() {     
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

llvm::Value* LetDef::codegen() {
    AST::st->scope_open();

    if(let_type == LetType::NoRec)
        AST::st->scope_hide(true);
    
    //The definitions are first added to the symboltable and then type inference and semantic analysis happens
    //This is to allow mutually recursive definitions ex.let rec even n = if n=0 then true else odd (n-1) and odd n = if n=0 then false else even (n-1)
    this->def->add_to_symbol_table();
    this->def->allocate();
    this->def->make_non_local_variable_stack();

    auto def_value = def->codegen();

    if(let_type == LetType::NoRec)
        AST::st->scope_hide(false);

    return def_value;
}