#ifndef __UNOP_HPP__
#define __UNOP_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include <iostream>
#include <memory>

class UnOp : public Expr{
public:
    UnOp(Expr* expr, OpType op): expr(expr), op(op) {}

    virtual ~UnOp() {
        delete expr;
    }

    virtual void print(std::ostream &out) const override {
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

    virtual std::shared_ptr<TypeVariable> infer() {
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

    virtual void sem() override { 
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

    virtual llvm::Value* codegen() const {
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

                //TODO: Implement this
                break;
            }
            default:
                std::cerr << "Unknown binary operator type\n";
                exit(1); //TODO:Error handling
                break;
        }  

        return nullptr;
    }

private:
    Expr* expr;
    OpType op;
};

#endif