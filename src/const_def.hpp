#ifndef __CONSTANTDEF_HPP__
#define __CONSTANTDEF_HPP__

#include "includes.hpp"

class ConstDef : public Def{
public:
    ConstDef(std::string* id, Expr* expr): id(*id), expr(expr), type(new Type(TypeTag::Unkown)) {}
    ConstDef(std::string* id, Type* type, Expr* expr): id(*id), type(type), expr(expr) {}

    virtual void print(std::ostream& out) const override{
        out << "ConstDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << " Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }
private:
    std::string id;
    Type* type;
    Expr* expr;
};

#endif