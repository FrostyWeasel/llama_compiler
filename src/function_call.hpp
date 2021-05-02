#ifndef __FUNCTIONCALL_HPP__
#define __FUNCTIONCALL_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "includes.hpp"


class FunctionCall : public Expr{
public:
    FunctionCall(std::string* id, Block<Expr>* expr_list) : id(*id), expr_list(expr_list) { }

    ~FunctionCall() {
	std::cout << "FunctionCall deleted\n";
        delete expr_list;
    }

    virtual void print(std::ostream &out) const override{
        out << "FunctionCall(";
        out << " Id: " << id << ", ";
        out << "Expr_list: ";
        if(expr_list != nullptr)
            expr_list->print(out);
        else
            out << "null ";
        out << ") ";
    }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif