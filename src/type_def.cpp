#include "type_def.hpp"
#include "type_variable.hpp"
#include "t_def.hpp"
#include "block.hpp"
#include <iostream>
#include <memory>

TypeDef::TypeDef(Block<TDef>* t_defs) : t_defs(t_defs) {

}

TypeDef::~TypeDef() {
    delete t_defs;
}

void TypeDef::print(std::ostream &out) const {
    out << "TypeDef(";
    out << "TDef: ";
    if(t_defs != nullptr)
        t_defs->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> TypeDef::infer() {
    AST::st->scope_open();

    auto t_def_list = this->t_defs->get_list(); 

    //The definitions are first added to the symboltable and then type inference and semantic analysis happens
    //This is to allow mutually recursive definitions ex.type tree = Leaf | Node of int forest and forest = Empty | NonEmpty of tree forest
    for(auto t_def: t_def_list) {
        t_def->add_to_symbol_table();
    }

    for(auto t_def: t_def_list) {
        t_def->infer();
    }

    return nullptr;
}

void TypeDef::sem() {
    AST::st->scope_open();

    auto t_def_list = this->t_defs->get_list(); 

    //The definitions are first added to the symboltable and then type inference and semantic analysis happens
    //This is to allow mutually recursive definitions ex.type tree = Leaf | Node of int forest and forest = Empty | NonEmpty of tree forest
    for(auto t_def: t_def_list) {
        t_def->add_to_symbol_table();
    }

    for(auto t_def: t_def_list) {
        t_def->sem();
    }
}

llvm::Value* TypeDef::codegen() {
    AST::st->scope_open();

    auto t_def_list = this->t_defs->get_list(); 

    //The definitions are first added to the symboltable and then type inference and semantic analysis happens
    //This is to allow mutually recursive definitions ex.type tree = Leaf | Node of int forest and forest = Empty | NonEmpty of tree forest
    llvm::Value* t_def_value;
    for(auto t_def: t_def_list) {
        t_def->add_to_symbol_table();

    }

    for(auto t_def: t_def_list) {
        t_def->allocate();
    }

    for(auto t_def: t_def_list) {
        t_def_value = t_def->codegen();
    }

    return t_def_value;
}