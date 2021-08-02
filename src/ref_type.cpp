#include "ref_type.hpp"
#include "type_variable.hpp"
#include <memory>
#include <iostream>
    
RefType::RefType(TypeVariable* type_variable) : type_variable(std::shared_ptr<TypeVariable>(type_variable)), Type(TypeTag::Reference) { 
    if(this->type_variable->get_tag() == TypeTag::Array) {
        std::cerr << "Referenced type can not be array.\n";
        exit(1); // TODO: Error handling + Should i do this?
    }
}
RefType::RefType(std::shared_ptr<TypeVariable> type_variable) : type_variable(type_variable), Type(TypeTag::Reference) { 
    if(this->type_variable->get_tag() == TypeTag::Array) {
        std::cerr << "Referenced type can not be array.\n";
        exit(1); // TODO: Error handling + Should i do this?
    }
}

RefType::~RefType() {  }

bool RefType::contains(std::shared_ptr<TypeVariable> type_variable) {
    return this->type_variable->contains(type_variable);
}

std::shared_ptr<TypeVariable> RefType::get_referenced_variable() {
    return this->type_variable;
}

void RefType::print(std::ostream &out) const{ 
    if (type_variable == nullptr)
        out << "TypeVariable: Null";
    else
        out << " (" << *type_variable << ") ref ";
}

unsigned int RefType::get_depth() {
    return (this->type_variable->get_tag() == TypeTag::Reference) ? (1 + this->type_variable->get_complex_type_depth()) : (1);
}

TypeTag RefType::get_bottom_tag() {
    return (this->type_variable->get_tag() != TypeTag::Reference) ? (this->type_variable->get_bottom_tag()) : (this->type_variable->get_tag());
}