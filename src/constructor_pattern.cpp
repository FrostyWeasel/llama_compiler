#include "constructor_pattern.hpp"
#include "type_variable.hpp"
#include "block.hpp"
#include "constructor_entry.hpp"
#include "type_entry.hpp"
#include <string>
#include <sstream>
#include <memory>

ConstructorPattern::ConstructorPattern(std::string* id, Block<Pattern>* pattern_list) : id(*id), pattern_list(pattern_list), Pattern(PatternType::Constructor, std::make_shared<TypeVariable>(TypeTag::Unknown)) {

}

void ConstructorPattern::print(std::ostream& out) const {
    out << id;
    out << ": ";
    if(pattern_list != nullptr) {
        pattern_list->print(out);
    }
    else {
        out << " null";
    }
}

std::shared_ptr<TypeVariable> ConstructorPattern::infer() {
    auto constr_entry = dynamic_cast<ConstructorEntry*>(st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES));

    //Check the pattern list with which the constructor was called and compare them to the constructor definition
    auto constructor_type_list = *(constr_entry->get_constructor_type_list());

    if(this->pattern_list != nullptr) {
        auto constructor_pattern_list = this->pattern_list->get_list();

        if(constructor_pattern_list.size() != constructor_type_list.size()) {
            std::stringstream msg;
            msg << "Constructor " << this->id << " called with wrong number of arguments: " << constructor_pattern_list.size() 
                << " instead of " <<  constructor_type_list.size() << ".\n";
            error_handler->print_error(msg.str(), ErrorType::User, this->lineno);
        }

        unsigned int i = 0;
        for(auto element_it = constructor_pattern_list.begin(); element_it != constructor_pattern_list.end(); element_it++) {
            if(*element_it != nullptr){
                std::shared_ptr<TypeVariable> constructor_pattern_type = (*element_it)->infer();
                auto constructor_expected_type = constructor_type_list[i++];
                st->add_constraint(constructor_pattern_type, constructor_expected_type, this->lineno);
            }
            else {
                error_handler->print_error("Nullptr in constructor pattern list.\n", ErrorType::Internal);
            }
        }
    }
    else {
        if(constructor_type_list.size() != 0) {
            error_handler->print_error("Constructor " + this->id + " called with wrong number of arguments: " + '0' + " instead of " + std::to_string(constructor_type_list.size()) + ".\n", ErrorType::User, this->lineno);
        }
    }

    st->add_constraint(this->type_variable, constr_entry->get_type(), this->lineno);

    return this->type_variable;
}

void ConstructorPattern::sem() {
    auto constr_entry = dynamic_cast<ConstructorEntry*>(st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES));
   //we might find ParEntries of the same name which we don't want so make sure its a type entry
    auto type_entry = dynamic_cast<TypeEntry*>(st->lookup_entry_of_type(constr_entry->get_type()->get_user_type_id(), EntryType::ENTRY_TYPE));
    
    //Check that user type which constructor constructs is currently the one in scope. For example here Red has type color but currently color has no constructor Red but Something and Else:
    /*
        type color = Red | Green | Blue
        type color = Something | Else
        let y = Else
        let x = match y with
                Red -> ... (* Red here is user_type color = Red | Green | Blue but that type is actually not in scope*) 
    */
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
            type_entry->get_type()->get_user_type_id() << " as was expected.\n";
        
        error_handler->print_error(msg.str(), ErrorType::User, this->lineno);
    }


    if(pattern_list != nullptr) {
        auto patterns = pattern_list->get_list();

        for(auto pattern: patterns) {
            pattern->sem();
        }
    }
}

llvm::Value* ConstructorPattern::codegen() {
    auto constr_entry = dynamic_cast<ConstructorEntry*>(st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES));

    std::vector<llvm::Value*> constructor_arg_values;    
    std::vector<llvm::Type*> constructor_arg_types;

    //First element holds the count which acts as an identifier(tag) for the constructor
    constructor_arg_types.push_back(i32);
    constructor_arg_values.push_back(c32(constr_entry->get_count()));

    for(auto pattern: this->pattern_list->get_list()) {
        auto pattern_value = pattern->codegen();

        constructor_arg_values.push_back(pattern_value);
        constructor_arg_types.push_back(pattern_value->getType());

    }

    //Store constructor type so that it can be accessed by match statement
    this->matching_constructor_llvm_type = constr_entry->get_llvm_type();

    
    auto constructor_struct_type = llvm::StructType::get(TheContext, constructor_arg_types);
    auto constructor_struct_heap_void_ptr = Builder.CreateCall(AST::malloc_function, { c32(TheDataLayout->getTypeAllocSize(constructor_struct_type).getValue()) }, this->id + std::to_string(constr_entry->get_count()) + "_constructor_pattern_struct_heap_void_ptr");

    auto constructor_struct_heap_ptr = Builder.CreateBitCast(constructor_struct_heap_void_ptr, llvm::PointerType::get(constructor_struct_type, 0), this->id + std::to_string(constr_entry->get_count()) + "_constructor_pattern_struct_heap_ptr");

    this->pattern_constructor_llvm_type = constructor_struct_type;
    this->llvm_type = constructor_struct_type;

    //Store expression values in costructor struct
    unsigned int i = 0;
    for(auto pattern_value: constructor_arg_values) {
        auto constr_struct_element_ptr = Builder.CreateStructGEP(constructor_struct_heap_ptr, i++, this->id + std::to_string(constr_entry->get_count()) + "_constructor_pattern_arg_ptr");
        Builder.CreateStore(pattern_value, constr_struct_element_ptr);
    }

    //Bitcast to same type as its user type (i8*)
    return Builder.CreateBitCast(constructor_struct_heap_ptr, map_to_llvm_type(this->type_variable));
}