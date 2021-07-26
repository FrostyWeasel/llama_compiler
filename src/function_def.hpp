#ifndef __FUNCTIONDEF_HPP__
#define __FUNCTIONDEF_HPP__

#include "enums.hpp"
#include "type.hpp"
#include "block.hpp"
#include "par.hpp"
#include "expr.hpp"
#include "def.hpp"
#include "symbol_entry.hpp"
#include "function_entry.hpp"
#include <string>
#include <iostream>
#include <map>

class FunctionEntry;

class FunctionDef : public Def {
public:
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr): id(*id), par_list(par_list), Def(new TypeVariable()), expr(expr), from_type(std::make_shared<TypeVariable>()) {}
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr, std::shared_ptr<TypeVariable> type_variable): id(*id), par_list(par_list), Def(type_variable), expr(expr), from_type(std::make_shared<TypeVariable>()) {}

    virtual ~FunctionDef() {
        delete expr;
        delete par_list;
    }

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override ;

    virtual void allocate() override ;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen();


private:
    std::string id;
    Block<Par>* par_list;
    Expr* expr;
    std::shared_ptr<TypeVariable> from_type;

    std::map<std::string, std::shared_ptr<TypeVariable>> non_local_variables;
};

#endif