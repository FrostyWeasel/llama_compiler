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
    auto entry = new TypeEntry(id, EntryType::ENTRY_TYPE, this->type_variable, this->constructor_list->get_list());

    st->insert_entry(entry);
    this->entry = entry;

    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->add_to_symbol_table(entry);
    }
}

void TDef::allocate()  {
    // auto t_def_type = llvm::dyn_cast<llvm::StructType>(map_to_llvm_type(this->type_variable));

    // auto t_def_struct = t_def_type->create(TheContext, { llvm::PointerType::get(AST::i8, 0) }, "user_type_" + this->id);

}

std::shared_ptr<TypeVariable> TDef::infer() {
    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->infer();
    }

    return this->type_variable;
}

void TDef::sem() {
    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->sem();
    }
}

llvm::Value* TDef::codegen() {
    //TODO: Generate code for a function that can take 2 elements of this type and perform structural check depending on there tag(use the tag to figure out which contructor of this class is used and then bitcast to the constructors type) (the tdefs entry should hold the function definition) .
    //TODO: Put a count in this class as a unique id for this tdef so that its comparison function is unique.

    auto constructors = this->constructor_list->get_list();

    for(auto constructor: constructors) {
        constructor->codegen();
    }

    // auto type_entry = dynamic_cast<TypeEntry*>(this->entry);
    // return type_entry->get_type_struct(); 
}