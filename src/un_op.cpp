#include "un_op.hpp"
    
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
        default:
            std::cerr << "ERROR: No known op "; //TODO: Error: Replace by error handling
            exit(1);
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

            this->st->add_constraint(expr_type, this->type_variable);
            break;
        case OpType::Plus:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(expr_type, this->type_variable);
            break;
        case OpType::Minus:
            expr_type = this->expr->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(expr_type, this->type_variable);
            break;
        case OpType::Dereference:{
            expr_type = this->expr->infer(); //Type must be t ref
            this->type_variable = std::make_shared<TypeVariable>(); //Type must be t

            this->st->add_constraint(expr_type, std::make_shared<TypeVariable>(TypeTag::Reference, this->type_variable));
            break;
        }
        default:
            std::cerr << "Unknown binary operator type\n";
            exit(1); //TODO:Error handling
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
        default:
            std::cerr << "Unknown binary operator type\n";
            exit(1); //TODO:Error handling
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
        default:
            std::cerr << "Unknown binary operator type\n";
            exit(1); //TODO:Error handling
            break;
    }  

    return nullptr;
}