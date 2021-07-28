#ifndef __FUNCTIONCALL_HPP__
#define __FUNCTIONCALL_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "function_entry.hpp"
#include "parameter_entry.hpp"
#include "enums.hpp"
#include "block.hpp"

class FunctionCall : public Expr{
public:
    FunctionCall(std::string* id, Block<Expr>* expr_list) : id(*id), expr_list(expr_list), Expr(new TypeVariable()) { }

    virtual ~FunctionCall() {
        delete expr_list;
    }

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;


private:
    std::string id;
    Block<Expr>* expr_list;

    llvm::Value* library_function_codegen();
};

#endif