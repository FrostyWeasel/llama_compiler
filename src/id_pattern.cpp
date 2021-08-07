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

}

llvm::Value* IdPattern::codegen() {
    auto type = map_to_llvm_type(this->type_variable);
    this->llvm_type = type;
    return Builder.CreateAlloca(type, nullptr, this->id+"_pattern");
}