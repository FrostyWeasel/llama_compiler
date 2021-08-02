#ifndef __ERROR_HANDLER_HPP__
#define __ERROR_HANDLER_HPP__

#include "enums.hpp"
#include "type_variable.hpp"
#include "ast.hpp"
#include <string>
#include <sstream>
#include <iostream>

class TypeVariable;

class ErrorHandler {
public:
    ErrorHandler() = default;
    ~ErrorHandler() = default;

    //Type errors
    void unbound_type(std::shared_ptr<TypeVariable> type_variable);
    void incompatible_types(std::shared_ptr<TypeVariable> t1, std::shared_ptr<TypeVariable> t2, unsigned int lineno);
    
    //Semantic errors
    void non_allowed_type(std::shared_ptr<TypeVariable> type, unsigned int lineno, ErrorType error_type, NodeType node_type);
    void non_allowed_type(std::shared_ptr<TypeVariable> type, std::string& id, unsigned int lineno,  ErrorType error_type, TypeTag type_tag);

    //Symbol table errors
    void out_of_scope(std::string id);
    void redefining_variable(std::string id);

    void print_error(std::string msg, ErrorType error_type);
    void print_error(std::string msg, ErrorType error_type, unsigned int lineno);

};

#endif