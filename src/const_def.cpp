#include "const_def.hpp"
#include "expr.hpp"
#include "constant_entry.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include <string>
#include <iostream>

ConstDef::ConstDef(std::string* id, Expr* expr): id(*id), expr(expr), Def(new TypeVariable()) {}
ConstDef::ConstDef(std::string* id, std::shared_ptr<TypeVariable> type_variable, Expr* expr): id(*id), Def(type_variable), expr(expr) {}

ConstDef::~ConstDef() {
    delete expr;
}

void ConstDef::print(std::ostream& out) const {
    out << " " << id;
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << " = ";
    if(expr != nullptr)
        expr->print(out);
    else
        out << " null";
}

void ConstDef::add_to_symbol_table() {
    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type_variable);
    
    st->insert_entry(entry);

    this->entry = entry;
}

void ConstDef::allocate() {
    llvm::AllocaInst* alloc_ptr = nullptr;
    alloc_ptr = Builder.CreateAlloca(map_to_llvm_type(this->type_variable), nullptr, id);
    this->entry->set_allocation(alloc_ptr);
}

std::shared_ptr<TypeVariable> ConstDef::infer() {
    auto expr_type = this->expr->infer();

    st->add_constraint(this->type_variable, expr_type, this->lineno);

    return this->type_variable;
}

void ConstDef::sem() { 
    this->expr->sem();
}

llvm::Value* ConstDef::codegen() {
    auto value = this->expr->codegen();

    if(value != nullptr) {
        auto store = Builder.CreateStore(value, this->entry->get_allocation());
        return store;
    }
    
    return nullptr;
}