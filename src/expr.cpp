#include "expr.hpp"
#include "type_variable.hpp"
#include <memory>

Expr::Expr() : AST(NodeType::Expr) {}

Expr::Expr(TypeVariable* type_variable): type_variable(std::shared_ptr<TypeVariable>(type_variable)), AST(NodeType::Expr) {
    AST::created_type_variables->push_back(this->type_variable);  
    AST::type_variable_owners->insert({ this->type_variable->get_id(), this });  
}

