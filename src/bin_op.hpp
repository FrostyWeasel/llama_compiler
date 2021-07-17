#ifndef __BINOP_HPP__
#define __BINOP_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
#include <iostream>

class BinOp : public Expr {
public:

    BinOp(Expr* lval, Expr* rval, OpType op): lval(lval), rval(rval), op(op) {}

    ~BinOp() {
        delete lval;
        delete rval;
    }

    virtual void print(std::ostream &out) const override {
        if(lval != nullptr)
            lval->print(out);
        else
            out << " null";

        switch(op){
            case OpType::And:
                out << " &&";
                break;
            case OpType::Assign:
                out << " :=";
                break;
            case OpType::Concat:
                out << " ;";
                break;
            case OpType::Divide:
                out << " /";
                break;
            case OpType::Equals:
                out << " =";
                break;
            case OpType::GreaterOrEqualThan:
                out << " >=";
                break;
            case OpType::GreaterThan:
                out << " >";
                break;
            case OpType::LessOrEqualThan:
                out << " <=";
                break;
            case OpType::LessThan:
                out << " <";
                break;
            case OpType::Minus:
                out << " -";
                break;
            case OpType::Modulo:
                out << " %";
                break;
            case OpType::NatEquals:
                out << " ==";
                break;
            case OpType::NatNotEquals:
                out << " !=";
                break;
            case OpType::NotEquals:
                out << " <>";
                break;
            case OpType::Or:
                out << " ||";
                break;
            case OpType::Plus:
                out << " +";
                break;
            case OpType::Times:
                out << " *";
                break;
            default:
                out << "ERROR: No known type "; //TODO: Error: Replace by error handling
                exit(1);
                break;
        }
        if(rval != nullptr)
            rval->print(out);
        else
            out << "null ";
    }

    virtual std::shared_ptr<TypeVariable> infer() {
        std::shared_ptr<TypeVariable> lval_type = nullptr;
        std::shared_ptr<TypeVariable> rval_type = nullptr;

        switch(op) {
            case OpType::And:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                //TODO: This and all other expressions like this leaks the new TypeVariable to fix replace all TV creations with shared pointers (cant be only in contraints cause when the constraint is gone the type will be deleted!).
                this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Bool));
                break;
            case OpType::Assign:
                lval_type = this->lval->infer(); //Type must be t ref
                rval_type = this->rval->infer(); //Type must be t
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Unit);

                //TODO: Check that this is right
                this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Reference, rval_type));
                break;
            case OpType::Concat:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = rval_type;

                break;
            case OpType::Divide:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

                this->st->add_constraint(lval_type, this->type_variable);
                this->st->add_constraint(rval_type, this->type_variable);
                break;
            case OpType::Equals:
                //TODO: Sem this can't be an array of a function type
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::GreaterOrEqualThan:
                //TODO: Sem this must be an int float or char
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::GreaterThan:
                //TODO: Sem this must be an int float or char
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::LessOrEqualThan:
                //TODO: Sem this must be an int float or char
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::LessThan:
                //TODO: Sem this must be an int float or char
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::Minus:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

                this->st->add_constraint(lval_type, this->type_variable);
                this->st->add_constraint(rval_type, this->type_variable);
                break;
            case OpType::Modulo:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

                this->st->add_constraint(lval_type, this->type_variable);
                this->st->add_constraint(rval_type, this->type_variable);
                break;
            case OpType::NatEquals:
                //TODO: Sem this can't be an array of a function type
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::NatNotEquals:
                //TODO: Sem this can't be an array of a function type
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::NotEquals:
                //TODO: Sem this can't be an array of a function type
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                break;
            case OpType::Or:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

                this->st->add_constraint(lval_type, rval_type);
                this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Bool));
                break;
            case OpType::Plus:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

                this->st->add_constraint(lval_type, this->type_variable);
                this->st->add_constraint(rval_type, this->type_variable);  
                break;
            case OpType::Times:
                lval_type = this->lval->infer();
                rval_type = this->rval->infer();
                this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

                this->st->add_constraint(lval_type, this->type_variable);
                this->st->add_constraint(rval_type, this->type_variable); 
                break;
            default:
                std::cerr << "Unknown binary operator type\n";
                exit(1); //TODO:Error handling
                break;
        }

        return this->type_variable;
    }


private:
    Expr* lval;
    Expr* rval;
    OpType op;
};

#endif