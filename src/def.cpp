#include "def.hpp"
#include "type_variable.hpp"
#include <memory>

Def::Def() : AST(NodeType::Def) {}

Def::Def(TypeVariable* type_variable) : type_variable(std::shared_ptr<TypeVariable>(type_variable)), AST(NodeType::Def) { 
    AST::created_type_variables->push_back(this->type_variable);
    AST::type_variable_owners->insert({ this->type_variable->get_id(), this }); 
}

Def::Def(std::shared_ptr<TypeVariable> type_variable) : type_variable(type_variable), AST(NodeType::Def) { 
    AST::created_type_variables->push_back(this->type_variable);
    AST::type_variable_owners->insert({ this->type_variable->get_id(), this });     
}