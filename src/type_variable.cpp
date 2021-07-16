#include "type_variable.hpp"
#include "type.hpp"
#include "function_type.hpp"
#include "array_type.hpp"
#include "ref_type.hpp"
#include "enums.hpp"
#include <memory>

unsigned int TypeVariable::counter = 0;

TypeVariable::TypeVariable() : type(std::make_shared<Type>(TypeTag::Unknown)), tag(TypeVariableTag::Free), id(++TypeVariable::counter) {  }

TypeVariable::TypeVariable(TypeTag type_tag) { 
    switch (type_tag) {
        case TypeTag::Unknown:
            this->type = std::make_shared<Type>(TypeTag::Unknown);
            this->tag = TypeVariableTag::Free;
            this->id = ++TypeVariable::counter;
            break;
        
        default:
            this->type = std::make_shared<Type>(type_tag);
            this->tag = TypeVariableTag::Bound;
            this->id = 0;
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, TypeVariable* t1) {
    switch (type_tag) {
        case TypeTag::Reference:
            this->type = std::make_shared<RefType>(t1);
            if(t1->is_bound()){
                this->tag = TypeVariableTag::Bound;
                this->id = 0;
            }
            else{
                this->tag = TypeVariableTag::Free;
                this->id = ++counter; 
            }
            break;
        
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1);
            if(t1->is_bound()){
                this->tag = TypeVariableTag::Bound;
                this->id = 0;
            }
            else{
                this->tag = TypeVariableTag::Free;
                this->id = ++counter; 
            }
            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking one type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, TypeVariable* from_type, TypeVariable* to_type) {
    switch (type_tag) {
        case TypeTag::Function:
            this->type = std::make_shared<FunctionType>(from_type, to_type);
            if(from_type->is_bound() && to_type->is_bound()){
                this->tag = TypeVariableTag::Bound;
                this->id = 0;
            }
            else{
                this->tag = TypeVariableTag::Free;
                this->id = ++counter; 
            }
            break;

        default:
            std::cerr << "Invalid TypeVariableTag non Function for constractor two type variable\n";
            exit(1);
            break;
    }
}

TypeVariable::TypeVariable(TypeTag type_tag, TypeVariable* t1, int dim) {
    switch (type_tag) {
        case TypeTag::Array:
            this->type = std::make_shared<ArrayType>(t1, dim);
            if(t1->is_bound()){
                this->tag = TypeVariableTag::Bound;
                this->id = 0;
            }
            else{
                this->tag = TypeVariableTag::Free;
                this->id = ++counter; 
            }
            break;

        default:
            std::cerr << "Invalid TypeVariableTag for constractor taking one type variable\n";
            exit(1);
            break;
    }
}

bool TypeVariable::contains(TypeVariable* type_variable) {
    if (this->id == type_variable->id)
        return true;
    else 
        return this->type->contains(type_variable);
}

void TypeVariable::bind(TypeVariable* bound_type) {
        switch (this->tag) {
        case TypeVariableTag::Free:
            //TODO: Remove from free list if i make one during error handling.
            this->type = bound_type->type;
            this->tag = bound_type->tag;
            break;

        case TypeVariableTag::Bound:
            std::cerr << "Attempting to bind already bound TypeVariable with Type: " << *type;
            exit(1); //TODO: Error handling
            break;
        
        default:
            std::cerr << "Unkown TypeVariableTag\n";
            exit(1); //TODO: Error handling
            break;
        }
    }

TypeVariable* TypeVariable::get_function_from_type() {
    if (this->type->get_tag() == TypeTag::Function) {
        auto function_ptr = std::dynamic_pointer_cast<FunctionType>(this->type);
        return function_ptr->get_from_type_variable();
    }
    else{
        std::cerr << "Requesting get_function_from_type but type is not a function\n";
        exit(1); //TODO: Error handling
    }
}

TypeVariable* TypeVariable::get_function_to_type() {
    if (this->type->get_tag() == TypeTag::Function) {
        auto function_ptr = std::dynamic_pointer_cast<FunctionType>(this->type);
        return function_ptr->get_to_type_variable();
    }
    else{
        std::cerr << "Requesting get_function_to_type but type is not a function\n";
        exit(1); //TODO: Error handling
    }
}

TypeVariable* TypeVariable::get_referenced_type() {
    if (this->type->get_tag() == TypeTag::Reference) {
        auto reference_ptr = std::dynamic_pointer_cast<RefType>(this->type);
        return reference_ptr->get_referenced_variable();
    }
    else{
        std::cerr << "Requesting get_referenced_variable but type is not a reference\n";
        exit(1); //TODO: Error handling
    }
}

TypeTag TypeVariable::get_tag() { return type->get_tag(); }
TypeVariableTag TypeVariable::get_variable_tag() { return this->tag; }

void TypeVariable::print(std::ostream& out) const { 
    switch(tag){
        case TypeVariableTag::Free:
            out << "@" << id << " " << *this->type;
            break;
        case TypeVariableTag::Bound:
            out << "@" << id << " " << *this->type;
            break;
        default:
            std::cerr << "Unknown TypeVariableTag\n";
            exit(1);
            break;
    }
}

bool TypeVariable::is_bound() {
    return this->tag == TypeVariableTag::Bound;
}
