#ifndef __FUNCTIONDEF_HPP__
#define __FUNCTIONDEF_HPP__

#include "enums.hpp"
#include "def.hpp"
#include <string>
#include <iostream>
#include <map>

class FunctionEntry;

template <class T>
class Block;

class Par;
class TypeVariable;
class Expr;

class FunctionDef : public Def {
public:
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr);
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr, std::shared_ptr<TypeVariable> type_variable);

    virtual ~FunctionDef();

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override ;

    virtual void allocate() override ;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen();

    virtual void make_non_local_variable_stack() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
    Block<Par>* par_list;
    Expr* expr;
    std::shared_ptr<TypeVariable> from_type;

    std::map<std::string, std::shared_ptr<TypeVariable>> non_local_variables;

    llvm::StructType* non_local_struct_type;
};

#endif