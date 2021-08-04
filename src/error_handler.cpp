#include "error_handler.hpp"
#include "def.hpp"


//Type errors
void ErrorHandler::unbound_type(std::shared_ptr<TypeVariable> type_variable) {
    
    std::cerr << "Warning: ";

    auto type_variable_owner = AST::type_variable_owners->find(type_variable->get_id());
    if(type_variable_owner != AST::type_variable_owners->end()) {
        std::cerr << "In line " << type_variable_owner->second->lineno;
        auto id = type_variable_owner->second->get_id();
        if(id != "") {
            std::cerr << " in " << id << ":\n";
        }
    }

    std::cerr << "\ttype variable @ "<< type_variable->get_id() << " was not substituted\n";
}

void ErrorHandler::incompatible_types(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2, unsigned int lineno) {
    std::cerr << "Error: In line " << lineno << ":\n";

    std::cerr << "\timpossible to unify "<< *t1 << " with " << *t2 << "\n";
    exit(1);
}

//Semantic errors
void ErrorHandler::non_allowed_type(std::shared_ptr<TypeVariable> type, unsigned int lineno, ErrorType error_type, NodeType node_type) {
    std::cerr << "Error: In line " << lineno << ":\n";
    switch(node_type) {
        case NodeType::BinOp:
            std::cerr << "\tin binary expression this type is not allowed:\n\t" << "offending type is: " << *type << "\n";
            break;
        case NodeType::UnOp:
            std::cerr << "\tin unary expression this type is not allowed:\n\t" << "offending type is: " << *type << "\n";
            break;
        case NodeType::New:
            std::cerr << "\tin new expression this type is not allowed\n\t" << "offending type is: " << *type << "\n";
        default:
            std::cerr << "\tin expression this type is not allowed:\n\t" << "offending type is: " << *type << "\n";
            break;
    }

    exit(1);
}

void ErrorHandler::non_allowed_type(std::shared_ptr<TypeVariable> type, std::string& id, unsigned int lineno,  ErrorType error_type, TypeTag type_tag) {
    std::cerr << "Error: In line " << lineno << ":\n";
    switch(type_tag) {
        case TypeTag::Function:
            std::cerr << "\tin function " << id << " return this type is not allowed:\n\t" << "offending type is: " << *(type->get_function_to_type()) << "\n";
            break;
        default:
            std::cerr << "\tin definition " << id << " this type is not allowed:\n\t" << *(type) << "\n";
            break;
    }
    exit(1);
}

//Symbol table errors
//TODO: Put lineno in error message by giving the lineno of the expression to lookup entry
void ErrorHandler::out_of_scope(std::string id) {
    std::cerr << "Error:\n";
    std::cerr << "\tVariable " << id << " is out of scope"; 
    exit(1);
}

//TODO: Put lineno in error message by giving the lineno of the expression to insert entry
void ErrorHandler::redefining_variable(std::string id) {
    std::cerr << "Error:\n";
    std::cerr << "\tVariable " << id << " is already defined in this scope"; 
    exit(1);
}


void ErrorHandler::print_error(std::string msg, ErrorType error_type) {
    switch(error_type) {
        case ErrorType::Warning:
            std::cerr << "Warning:\n\t";
            std::cerr << msg;
            break;
        case ErrorType::User:
            std::cerr << "Error:\n\t";
            std::cerr << msg;
            exit(1);
            break;
        case ErrorType::Internal:
            std::cerr << "Internal Error:\n\t";
            std::cerr << msg;
            exit(1);
        default:
            std::cerr << msg;
            exit(1);
    }
}

void ErrorHandler::print_error(std::string msg, ErrorType error_type, unsigned int lineno) {
    switch(error_type) {
        case ErrorType::Warning:
            std::cerr << "Warning: In line " << lineno << ":\n\t";
            std::cerr << msg;
            break;
        case ErrorType::User:
            std::cerr << "Error: In line " << lineno << ":\n\t";
            std::cerr << msg;
            exit(1);
            break;
        case ErrorType::Internal:
            std::cerr << "Internal Error: In line " << lineno << ":\n\t";
            std::cerr << msg;
            exit(1);
        default:
            std::cerr << msg;
            exit(1);
    }
}
