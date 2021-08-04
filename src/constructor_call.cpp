#include "constructor_call.hpp"
#include "expr.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "enums.hpp"
#include "block.hpp"
#include "type_variable.hpp"
#include "constructor_entry.hpp"
#include <string>
#include <iostream>
#include <memory>
    
ConstructorCall::ConstructorCall(std::string* id) : id(*id), expr_list(nullptr) {

}

ConstructorCall::ConstructorCall(std::string* id, Block<Expr>* expr_list) : id(*id), expr_list(expr_list) {
    
}

ConstructorCall::~ConstructorCall() {

}

void ConstructorCall::print(std::ostream &out) const {
    out << "ConstructorCall(";
    out << " Id: " << id << ", ";
    out << "Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << "Expr_list: ";
    if(expr_list != nullptr)
        expr_list->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> ConstructorCall::infer() {
    auto entry = dynamic_cast<ConstructorEntry*>(st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES));

    auto constructor_type_list = *entry->get_constructor_type_list();

    if(this->expr_list != nullptr) {
        auto constructor_expr_list = this->expr_list->get_list();

        if(constructor_expr_list.size() != constructor_type_list.size()) {
            error_handler->print_error("Constructor " + this->id + " called with wrong number of arguments: " + std::to_string(constructor_expr_list.size()) + " instead of " +  std::to_string(constructor_type_list.size()) + ".\n", ErrorType::User, this->lineno);
        }

        unsigned int i = 0;
        for(auto element_it = constructor_expr_list.begin(); element_it != constructor_expr_list.end(); element_it++) {
            if(*element_it != nullptr){
                std::shared_ptr<TypeVariable> constructor_expr_type = (*element_it)->infer();
                auto constructor_expected_type = constructor_type_list[i++];
                st->add_constraint(constructor_expr_type, constructor_expected_type, this->lineno);
            }
            else {
                error_handler->print_error("Nullptr in constructor type list.\n", ErrorType::Internal);
            }
        }
    }
    else {
        if(constructor_type_list.size() != 0) {
            error_handler->print_error("Constructor " + this->id + " called with wrong number of arguments: " + '0' + " instead of " + std::to_string(constructor_type_list.size()) + ".\n", ErrorType::User, this->lineno);
        }
    }

    this->type_variable = entry->get_type();

    return this->type_variable;
}

void ConstructorCall::sem() {

}

llvm::Value* ConstructorCall::codegen() {

}
