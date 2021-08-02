#include "type.hpp"
#include "error_handler.hpp"
#include "type_variable.hpp"
#include <iostream>
#include <memory>
#include <string>
    
std::unique_ptr<ErrorHandler> Type::error_handler = std::make_unique<ErrorHandler>();

Type::Type() : tag(TypeTag::Unknown) {  }
Type::Type(TypeTag type) : tag(type) {  }

Type::~Type() { }

TypeTag Type::get_tag() { return tag; };
void Type::set_tag(TypeTag tag) { this->tag = tag; }

void Type::print(std::ostream& out) const { 
    switch(tag){
        case TypeTag::Bool:
            out << " bool";
            break;
        case TypeTag::Char:
            out << " char";
            break;
        case TypeTag::Int:
            out << " int";
            break;
        case TypeTag::Float:
            out << " float";
        break;
        case TypeTag::Unit:
            out << " unit";
            break;
        case TypeTag::Unknown:
            out << " unknown";
            break;
        case TypeTag::Array:
            this->print(out);
            break;
        case TypeTag::Function:
            this->print(out);
            break;
        case TypeTag::Reference:
            this->print(out);
            break;
        default:
            std::cerr << "Unknown typetag\n";
            exit(1);
            break;
    }
    out << " ";
}

bool Type::contains(std::shared_ptr<TypeVariable> type_variable) {
    return false;
}