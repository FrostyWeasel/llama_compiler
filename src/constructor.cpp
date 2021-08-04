#include "constructor.hpp"
#include "type_variable.hpp"
#include "symbol_table.hpp"
#include "block.hpp"
#include "type_entry.hpp"
#include "constructor_entry.hpp"
#include <string>
#include <memory>
#include <iostream>

unsigned int Constructor::counter = 0;

Constructor::Constructor(std::string* id) : id(*id), type_list(new std::vector<std::shared_ptr<TypeVariable>>()) {
    this->count = Constructor::counter++;
}
Constructor::Constructor(std::string* id, std::vector<std::shared_ptr<TypeVariable>>* type_list) : id(*id), type_list(type_list) {
    this->count = Constructor::counter++;
}

Constructor::~Constructor() {
    delete type_list;
}

void Constructor::print(std::ostream& out) const {
    out << "Constructor(";
    out << " Id: " << id;
    out << " Type_constructed: ";
    if(type_constructed != nullptr)
        type_constructed->print(out);
    else
        out << "null ";
    out << ", types: ";
    if(type_list != nullptr)
        for(auto type: *type_list) {
            type->print(out);
        }
    else
        out << "null ";
    out << ") ";
}

void Constructor::add_to_symbol_table() {

}

void Constructor::add_to_symbol_table(TypeEntry* owner_type) {
    this->type_constructed = owner_type->get_type();

    auto entry = new ConstructorEntry(id, EntryType::ENTRY_CONSTRACTOR, this->type_constructed, count, this->type_list);

    st->insert_entry(entry);
    this->entry = entry;

}

void Constructor::allocate() {

}

std::shared_ptr<TypeVariable> Constructor::infer() {

    return this->type_constructed;

}

void Constructor::sem() {

}

llvm::Value* Constructor::codegen() {

}
