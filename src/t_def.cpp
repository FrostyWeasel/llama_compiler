#include "t_def.hpp"
#include "type_variable.hpp"
#include "constructor.hpp"
#include "symbol_table.hpp"
#include "block.hpp"
#include "type_entry.hpp"
#include <string>
#include <memory>
#include <iostream>

TDef::TDef(std::string* id, Block<Constructor>* constructor_list) : id(*id), constructor_list(constructor_list), type_variable(std::make_shared<TypeVariable>(TypeTag::UserType, *id)) {

}

TDef::~TDef() {
    delete constructor_list;
}

void TDef::print(std::ostream& out) const {
    out << "TDef(";
    out << " Id: " << id;
    out << " Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << ", constructor_list: ";
    if(constructor_list != nullptr)
        constructor_list->print(out);
    else
        out << "null ";
    out << ") ";
}

void TDef::add_to_symbol_table()  {
    auto entry = new TypeEntry(id, EntryType::ENTRY_TYPE, this->type_variable);

    st->insert_entry(entry);
    this->entry = entry;

    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->add_to_symbol_table(entry);
    }
}

void TDef::allocate()  {

}

std::shared_ptr<TypeVariable> TDef::infer() {
    auto type_entry = dynamic_cast<TypeEntry*>(this->entry);

    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->infer();
    }

    return this->type_variable;
}

void TDef::sem() {

}

llvm::Value* TDef::codegen() {

}