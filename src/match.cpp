#include "match.hpp"
#include "expr.hpp"
#include "clause.hpp"
#include "type_variable.hpp"
#include "block.hpp"
#include <iostream>
#include <memory>
    
Match::Match(Expr* expr, Block<Clause>* clause_list) : expr(expr), clause_list(clause_list), Expr(new TypeVariable(TypeTag::Unknown)) {

}

Match::~Match() {
    delete expr;
    delete clause_list;
}


void Match::print(std::ostream &out) const {
    out << "Match(";
    out << "Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << "Clause_list: ";
    if(clause_list != nullptr)
        clause_list->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> Match::infer() {

}

void Match::sem() {

}

llvm::Value* Match::codegen() {

}