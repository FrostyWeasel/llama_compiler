#ifndef __UNOP_HPP__
#define __UNOP_HPP__

#include "expr.hpp"
#include "includes.hpp"


class UnOp : public Expr{
public:
    UnOp(Expr* expr, OpType op): expr(expr), op(op) {}

    ~UnOp() {
        delete expr;
    }

    virtual void print(std::ostream &out) const override {
        out << "UnOp(";
        out << "Type: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << "Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << "OpType: ";
        switch(op){
            case OpType::And:
                out << "And ";
                break;
            case OpType::Assign:
                out << "Assign ";
                break;
            case OpType::Concat:
                out << "Concat ";
                break;
            case OpType::Dereference:
                out << "Dereference ";
                break;
            case OpType::Divide:
                out << "Divide ";
                break;
            case OpType::Equals:
                out << "Equals ";
                break;
            case OpType::GreaterOrEqualThan:
                out << "GreaterOrEqualThan ";
                break;
            case OpType::GreaterThan:
                out << "GreaterThan ";
                break;
            case OpType::LessOrEqualThan:
                out << "LessOrEqualThan ";
                break;
            case OpType::LessThan:
                out << "LessThan ";
                break;
            case OpType::Minus:
                out << "Minus ";
                break;
            case OpType::Modulo:
                out << "Modulo ";
                break;
            case OpType::NatEquals:
                out << "NatEquals ";
                break;
            case OpType::NatNotEquals:
                out << "NatNotEquals ";
                break;
            case OpType::Not:
                out << "Not ";
                break;
            case OpType::NotEquals:
                out << "NotEquals ";
                break;
            case OpType::Or:
                out << "Or ";
                break;
            case OpType::Plus:
                out << "Plus ";
                break;
            case OpType::Times:
                out << "Times ";
                break;
            default:
                out << "ERROR: No known op "; //TODO: Error: Replace by error handling
                exit(1);
                break;
        }
        out << ") ";
    }

    virtual TypeVariable* infer() {
        TypeVariable* expr_type = nullptr;

        switch(op) {
            case OpType::Not:
                expr_type = this->expr->infer();
                this->type_variable = new TypeVariable(TypeTag::Bool);

                this->st->add_constraint(expr_type, this->type_variable);
                break;
            case OpType::Plus:
                expr_type = this->expr->infer();
                this->type_variable = new TypeVariable(TypeTag::Int);

                this->st->add_constraint(expr_type, this->type_variable);
                break;
            case OpType::Minus:
                expr_type = this->expr->infer();
                this->type_variable = new TypeVariable(TypeTag::Int);

                this->st->add_constraint(expr_type, this->type_variable);
                break;
            case OpType::Dereference:{
                //TODO: Check that this is correct

                expr_type = this->expr->infer(); //Type must be t ref
                this->type_variable = new TypeVariable(); //Type must be t

                this->st->add_constraint(expr_type, new TypeVariable(TypeTag::Reference, this->type_variable));
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