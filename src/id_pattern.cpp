#include "id_pattern.hpp"
#include "type_variable.hpp"
#include "constant_entry.hpp"
#include "symbol_table.hpp"
#include <string>
#include <memory>
#include <iostream>

IdPattern::IdPattern(std::string* id) : id(*id), Pattern(PatternType::Id, std::make_shared<TypeVariable>(TypeTag::Unknown)) {

}

void IdPattern::print(std::ostream& out) const {
    out << "(" << id << ": " << *this->type_variable << ") ";
}

std::shared_ptr<TypeVariable> IdPattern::infer() {
    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type_variable);

    st->insert_entry(entry);

    return this->type_variable;
}

void IdPattern::sem() {
    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type_variable);

    st->insert_entry(entry);
}

llvm::Value* IdPattern::codegen() {
    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, this->type_variable);

    auto type = map_to_llvm_type(this->type_variable);
    this->llvm_type = type;

    auto id_alloca = Builder.CreateAlloca(type, nullptr, this->id+"_pattern");

    entry->set_allocation(id_alloca);

    st->insert_entry(entry);

    return id_alloca;
}