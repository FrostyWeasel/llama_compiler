#ifndef __BINOP_HPP__
#define __BINOP_HPP__

#include "expr.hpp"
#include "includes.hpp"


class BinOp : public Expr{
public:
    BinOp(Expr* lval, Expr* rval, OpType op): lval(lval), rval(rval), op(op) {}

    ~BinOp() {
        delete lval;
        delete rval;
    }

    virtual void print(std::ostream &out) const override {
        out << "BinOp(";
        out << "lval: ";
        if(lval != nullptr)
            lval->print(out);
        else
            out << "null ";
        out << "rval: ";
        if(rval != nullptr)
            rval->print(out);
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
                out << "ERROR: No known type "; //TODO: Error: Replace by error handling
                exit(1);
                break;
        }
        out << ") ";
    }

    virtual Type* infer() {
        
    }


private:
    Expr* lval;
    Expr* rval;
    OpType op;
};

#endif