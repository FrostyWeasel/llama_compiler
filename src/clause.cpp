#include "clause.hpp"
#include "pattern.hpp"
#include "expr.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
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
    error_handler->print_error("Unimplemented clause infer was called\n", ErrorType::Internal);
    return this->infer_expression(); //never reached
}

std::shared_ptr<TypeVariable> Clause::infer_pattern() {
    return this->pattern->infer();
}

std::shared_ptr<TypeVariable> Clause::infer_expression() {
    return this->expr->infer();
}

void Clause::sem() {
    this->pattern->sem();
    this->expr->sem();
}

llvm::Value* Clause::codegen() {
    error_handler->print_error("Unimplemented clause codegen was called\n", ErrorType::Internal);
    return this->codegen_expression(); //never reached
}

llvm::Value* Clause::codegen_pattern() {
    return this->pattern->codegen();
}

llvm::Value* Clause::codegen_expression() {
    return this->expr->codegen();
}

llvm::Type* Clause::get_clause_pattern_llvm_type() {
    return this->pattern->get_llvm_type();
}

PatternType Clause::get_clause_pattern_type() {
    return this->pattern->get_pattern_type();
}
