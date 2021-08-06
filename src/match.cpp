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
    out << " Clause_list: ";
    if(clause_list != nullptr)
        clause_list->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> Match::infer() {
    auto expr_type = this->expr->infer();

    auto clauses =  this->clause_list->get_list();

    //At the start of each clause a new scope is opened and ids defined in the clauses pattern are in scope only in the clauses expression
    st->scope_open();

    //All patterns must be of same type t which matches the expr type
    auto clause_pattern_type = clauses[0]->infer_pattern();
    st->add_constraint(expr_type, clause_pattern_type, this->lineno);

    //All expressions must have the same type which is the same as the type of the match statement
    auto clause_expr_type = clauses[0]->infer_expression();
    st->add_constraint(this->type_variable, clause_expr_type, this->lineno);

    st->scope_close();

    for(auto clause_it = ++clauses.begin(); clause_it != clauses.end(); clause_it++) {
        st->scope_open();

        auto other_clause_pattern_type = (*clause_it)->infer_pattern();
        st->add_constraint(clause_pattern_type, other_clause_pattern_type, this->lineno);

        auto other_clause_expr_type = (*clause_it)->infer_expression();
        st->add_constraint(clause_expr_type, other_clause_expr_type, this->lineno);

        st->scope_close();
    }

    return this->type_variable;
}

void Match::sem() {
    this->expr->sem();

    auto clauses =  this->clause_list->get_list();

    //At the start of each clause a new scope is opened and ids defined in the clauses pattern are in scope only in the clauses expression
    st->scope_open();

    for(auto clause_it = clauses.begin(); clause_it != clauses.end(); clause_it++) {
        st->scope_open();

        (*clause_it)->sem();

        st->scope_close();
    }

    //The expr type (and thus all pattern types) must be user_types
    if(sa->is_not_same_tag(this->expr->get_type(), TypeTag::UserType)) {
        error_handler->non_allowed_type(this->expr->get_type(), this->lineno, ErrorType::User, NodeType::Expr);
    }
}

llvm::Value* Match::codegen() {

}