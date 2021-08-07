#ifndef __CLAUSE_HPP__
#define __CLAUSE_HPP__

#include "ast.hpp"
#include <iostream>
#include <memory>

class Pattern;
class Expr;
class TypeVariable;

class Clause : public AST {
public:
    Clause(Pattern* pattern, Expr* expr);
    virtual ~Clause();

    virtual void print(std::ostream& out) const override;
    virtual std::shared_ptr<TypeVariable> infer() override;
    virtual void sem() override;
    virtual llvm::Value* codegen() override;

    std::shared_ptr<TypeVariable> infer_pattern();
    std::shared_ptr<TypeVariable> infer_expression();

    llvm::Value* codegen_pattern();
    llvm::Value* codegen_expression();

    llvm::Type* get_clause_pattern_llvm_type();

    PatternType get_clause_pattern_type();

    inline Pattern* get_pattern() { return this->pattern; }
    inline Expr* get_expr() { return this->expr; }

private:
    Pattern* pattern;
    Expr* expr;
};

#endif