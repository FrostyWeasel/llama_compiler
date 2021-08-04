#ifndef __MATCH_HPP__
#define __MATCH_HPP__

#include "expr.hpp"
#include "block.hpp"

class Clause;

class Match : public Expr {
public:
    Match(Expr* expr, Block<Clause>* clause_list);

    virtual ~Match();

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    Expr* expr;
    Block<Clause>* clause_list;
};

#endif