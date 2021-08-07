#include "constructor_call.hpp"
#include "expr.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "enums.hpp"
#include "block.hpp"
#include "type_variable.hpp"
#include "constructor_entry.hpp"
#include "type_entry.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
    
ConstructorCall::ConstructorCall(std::string* id) : id(*id), expr_list(nullptr) {

}

ConstructorCall::ConstructorCall(std::string* id, Block<Expr>* expr_list) : id(*id), expr_list(expr_list) {
    
}

ConstructorCall::~ConstructorCall() {

    if(this->expr_list != nullptr)
        delete this->expr_list;

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
    
    //Check that user type which constructor constructs is currently the one in scope. For example here Red has type color but currently color has no constructor Red but Something and Else:
    /*
        type color = Red | Green | Blue
        type color = Something | Else
        let y = Red 
    */
    auto type_entry = dynamic_cast<TypeEntry*>(st->lookup_entry(entry->get_type()->get_user_type_id(), LookupType::LOOKUP_ALL_SCOPES));
    auto includes_this_constructor = false;
    for(auto constructor: type_entry->get_constructors()) {
        if(constructor->get_id() == this->id) {
            includes_this_constructor = true;
            break;
        }
    }

    if(!includes_this_constructor) {
        std::stringstream msg;
        msg << "The constructor " << this->id << " does not belong to type " <<
            entry->get_type()->get_user_type_id() << " as was expected.\n";
        
        error_handler->print_error(msg.str(), ErrorType::User, this->lineno);
    }

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
                error_handler->print_error("Nullptr in constructor expr list.\n", ErrorType::Internal);
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
    auto constr_entry = dynamic_cast<ConstructorEntry*>(st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES));
    
    std::vector<llvm::Type*> constructor_arg_types;

    //First element holds the count which acts as an identifier for the constructor
    constructor_arg_types.push_back(i32);
    for(auto type: *(constr_entry->get_constructor_type_list())) {
        constructor_arg_types.push_back(map_to_llvm_type(type));
    }
    auto constructor_struct_type = llvm::StructType::get(TheContext, constructor_arg_types);
    auto constructor_alloca = Builder.CreateAlloca(constructor_struct_type, nullptr, this->id + std::to_string(constr_entry->get_count()) + "_constructor");

    //Store tag in constructor struct
    auto constr_struct_element_ptr = Builder.CreateStructGEP(constructor_alloca, 0, this->id + std::to_string(constr_entry->get_count()) + "_constructor_tag_ptr");
    Builder.CreateStore(c32(constr_entry->get_count()), constr_struct_element_ptr);
    

    //Store expression values in costructor struct
    if(this->expr_list != nullptr) {
        unsigned int i = 1;
        for(auto expr: this->expr_list->get_list()) {
            auto expr_value = expr->codegen();
            constr_struct_element_ptr = Builder.CreateStructGEP(constructor_alloca, i++, this->id + std::to_string(constr_entry->get_count()) + "_constructor_arg_ptr");
            Builder.CreateStore(expr_value, constr_struct_element_ptr);
        }
    }

    //Store alloca in constructors entry
    constr_entry->set_allocation(constructor_alloca);

    //Bitcast to same type as its type
    return Builder.CreateBitCast(constructor_alloca, map_to_llvm_type(this->type_variable));
}
