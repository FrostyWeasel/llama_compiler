#include "const_def.hpp"

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

    st->add_constraint(this->type_variable, expr_type);

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
    else
        return nullptr;
}