#include "clause.hpp"
#include "pattern.hpp"
#include "expr.hpp"
#include "type_variable.hpp"
#include <iostream>
#include <memory>

Clause::Clause(Pattern* pattern, Expr* expr) : pattern(pattern), expr(expr) {

}

Clause::~Clause() {
    delete expr;
    delete pattern;
}

void Clause::print(std::ostream& out) const {
    out << "( ";
    this->pattern->print(out);
    out << " -> ";
    this->expr->print(out) ;
    out << ") ";
}

std::shared_ptr<TypeVariable> Clause::infer() {
    this->infer_pattern();
    return this->infer_expression();
}

std::shared_ptr<TypeVariable> Clause::infer_pattern() {
    return this->pattern->infer();
}

std::shared_ptr<TypeVariable> Clause::infer_expression() {
    return this->expr->infer();
}

void Clause::sem() {
    //Semantic checks happen in match expr.
}

llvm::Value* Clause::codegen() {

}
