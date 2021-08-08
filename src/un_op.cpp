#include "un_op.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include <iostream>
#include <memory>

UnOp::UnOp(Expr* expr, OpType op): expr(expr), op(op) {}

UnOp::~UnOp() {
    delete expr;
}
    
void UnOp::print(std::ostream &out) const {
    switch(op){
        case OpType::Dereference:
            out << " !";
            break;
        case OpType::Minus:
            out << " -";
            break;
        case OpType::Not:
            out << " not";
            break;
        case OpType::Plus:
            out << " +";
            break;
        case OpType::PlusFloat:
            out << " +.";
            break;
        case OpType::MinusFloat:
            out << " -.";
            break;
        default:
            error_handler->print_error("Unknown unary operator type\n", ErrorType::Internal, this->lineno);

            break;
    }
    if(expr != nullptr)
        expr->print(out);
}

std::shared_ptr<TypeVariable> UnOp::infer() {
    std::shared_ptr<TypeVariable> expr_type = nullptr;

    switch(op) {
        case OpType::Not:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(expr_type, this->type_variable, this->lineno);
            break;
        case OpType::Plus:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(expr_type, this->type_variable, this->lineno);
            break;
        case OpType::Minus:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(expr_type, this->type_variable, this->lineno);
            break;
        case OpType::Dereference: {
            expr_type = this->expr->infer(); //Type must be t ref
            this->type_variable = std::make_shared<TypeVariable>(); //Type must be t

            this->created_type_variables->push_back(this->type_variable);

            this->st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Reference, this->type_variable), this->lineno);
            break;
        }
        case OpType::PlusFloat:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(expr_type, this->type_variable, this->lineno); 
            break;
        case OpType::MinusFloat:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(expr_type, this->type_variable, this->lineno); 
            break;
        default:
            error_handler->print_error("Unknown unary operator type\n", ErrorType::Internal, this->lineno);

            break;
    }

    return this->type_variable;
}

void UnOp::sem() { 
    switch(op) {
        case OpType::Not:
            this->expr->sem();
            
            break;
        case OpType::Plus:
            this->expr->sem();

            break;
        case OpType::Minus:
            this->expr->sem();

            break;
        case OpType::Dereference:{
            this->expr->sem(); //Type must be t ref

            break;
        }
        case OpType::PlusFloat:
            this->expr->sem();
            
            break;
        case OpType::MinusFloat:
            this->expr->sem();

            break;
        default:
            error_handler->print_error("Unknown unary operator type\n", ErrorType::Internal, this->lineno);

            break;
    }  
}

llvm::Value* UnOp::codegen() {
    llvm::Value* rhs = nullptr;

    switch(op) {
        case OpType::Not:
            rhs = this->expr->codegen();
            
            return Builder.CreateNot(rhs, "nottmp");
            break;
        case OpType::Plus:
            rhs = this->expr->codegen();

            return rhs;
            break;
        case OpType::Minus:
            rhs = this->expr->codegen();

            return Builder.CreateNeg(rhs, "negtmp");
            break;
        case OpType::Dereference:{
            rhs = this->expr->codegen();

            return Builder.CreateLoad(rhs, "dereference");
            break;
        }
        case OpType::PlusFloat:
            rhs = this->expr->codegen();

            return rhs;
            break;
        case OpType::MinusFloat:
            rhs = this->expr->codegen();

            return Builder.CreateFNeg(rhs, "float_negtmp");
            break;
        default:
            error_handler->print_error("Unknown unary operator type\n", ErrorType::Internal, this->lineno);

            break;
    }  

    return nullptr;
}