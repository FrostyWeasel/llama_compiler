#ifndef __T_DEF_HPP__
#define __T_DEF_HPP__

#include "ast.hpp"
#include "enums.hpp"
#include "block.hpp"
#include <string>
#include <memory>
#include <iostream>

class SymbolEntry;
class TypeVariable;
class Constructor;
class TypeEntry;

class TDef : public AST {
public:
    TDef(std::string* id, Block<Constructor>* constructor_list);

    virtual ~TDef();

    virtual void print(std::ostream& out) const override;

    virtual void add_to_symbol_table() override ;

    virtual void allocate() override ;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

    void set_type(std::shared_ptr<TypeVariable> type_variable) { this->type_variable = type_variable; }
    std::shared_ptr<TypeVariable> get_type() { return this->type_variable; }

    TypeEntry* get_entry() { return this->entry; }

private:
    std::string id;
    Block<Constructor>* constructor_list;
    std::shared_ptr<TypeVariable> type_variable;

    unsigned int count;
    static unsigned int counter;

    llvm::Function* user_type_comparison_function;

    //The entry in the ST corresponding to this definition 
    //* Do not delete this it is owned by the ST.
    TypeEntry* entry; 
};

#endif