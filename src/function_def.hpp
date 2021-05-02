#ifndef __FUNCTIONDEF_HPP__
#define __FUNCTIONDEF_HPP__

#include "includes.hpp"

class FunctionDef : public Def{
public:
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr): id(*id), par_list(par_list), Def(new Type(TypeTag::Unknown)), expr(expr) {}
    FunctionDef(std::string* id, Block<Par>* par_list, Expr* expr, Type* type): id(*id), par_list(par_list), Def(type), expr(expr) {}

    ~FunctionDef() {
	std::cout << "FunctionDef deleted\n";
        delete expr;
        delete par_list;
    }

    virtual void print(std::ostream& out) const override{
        out << "FunctionDef(";
        out << " Id: " << id;
        out << " Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << ", Par_list: ";
        if(par_list != nullptr)
            par_list->print(out);
        else
            out << "null ";
        out << ", Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }
private:
    std::string id;
    Block<Par>* par_list;
    Expr* expr;
};

#endif