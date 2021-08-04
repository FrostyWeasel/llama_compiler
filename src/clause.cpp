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

}

std::shared_ptr<TypeVariable> Clause::infer() {

}

void Clause::sem() {

}

llvm::Value* Clause::codegen() {

}
