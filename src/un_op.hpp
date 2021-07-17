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

    ~UnOp()  {}

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

private:
    Expr* expr;
    OpType op;
};

#endif