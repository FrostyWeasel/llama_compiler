
#include "user_type.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include <iostream>
#include <string>

UserType::UserType(std::string id) : id(id), Type(TypeTag::UserType) {

}

UserType::~UserType() { }

bool UserType::contains(std::shared_ptr<TypeVariable> type_variable) {
    return false;
}


void UserType::print(std::ostream &out) const{ 
    out << " " << id;
}