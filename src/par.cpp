#include "par.hpp"
#include "symbol_entry.hpp"
#include "parameter_entry.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include <string>
#include <iostream>

Par::Par(std::string* id): id(*id), type_variable(std::make_shared<TypeVariable>()), AST(NodeType::Par) {
    AST::type_variable_owners->insert({ this->type_variable->get_id(), this });
}
Par::Par(std::string* id, std::shared_ptr<TypeVariable> type_variable): id(*id), type_variable(type_variable), AST(NodeType::Par) {  
    AST::type_variable_owners->insert({ this->type_variable->get_id(), this });
}

void Par::print(std::ostream &out) const { 
    out << "(" << id << " :";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << " null";
    out << ")";
}

std::shared_ptr<TypeVariable> Par::infer() {
    ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type_variable);

    st->insert_entry(entry);

    AST::created_type_variables->push_back(this->type_variable);

    return this->type_variable;
}

void Par::set_type(std::shared_ptr<TypeVariable> type_variable) { this->type_variable = type_variable; }
std::shared_ptr<TypeVariable> Par::get_type() { return this->type_variable; }

void Par::sem() {
    ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type_variable);

    st->insert_entry(entry);

    switch(this->type_variable->get_tag()) {
        case TypeTag::Function : {
            auto to_type = this->type_variable->get_function_to_type();
            if((sa->is_same_tag(to_type, TypeTag::Function))) {
                error_handler->non_allowed_type(this->type_variable, id, this->lineno, ErrorType::User, TypeTag::Function);
            }
            // if((sa->is_same_tag(to_type, TypeTag::Array))) {
            //     error_handler->print_error("Function " << id << " return type can not be of type array\n" << "offending type is: " << *to_type, ErrorType::Internal);
            // }      
        }
        break;
        default:
        break;
    }
}

llvm::Value* Par::codegen() {
    ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type_variable);

    st->insert_entry(entry);

    auto alloc_ptr = Builder.CreateAlloca(map_to_llvm_type(this->type_variable), nullptr, id);

    entry->set_allocation(alloc_ptr);
    return alloc_ptr;
}

std::string Par::get_id() { return this->id; }