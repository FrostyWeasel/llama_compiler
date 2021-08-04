#ifndef __CONSTRUCTOR_CALL_HPP__
#define __CONSTRUCTOR_CALL_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "function_entry.hpp"
#include "parameter_entry.hpp"
#include "enums.hpp"
#include "block.hpp"

class ConstructorCall : public Expr{
public:
    ConstructorCall(std::string* id);
    ConstructorCall(std::string* id, Block<Expr>* expr_list);

    virtual ~ConstructorCall();

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }


private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif