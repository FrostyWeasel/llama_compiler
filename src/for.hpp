#ifndef __FOR_HPP__
#define __FOR_HPP__

#include "expr.hpp"
#include "includes.hpp"


class For : public Expr{
public:
    For() {}
    For(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr): id(*id), first_condition(first_condition), second_condition(second_condition), expr(expr) {}

    ~For() {
	std::cout << "For deleted\n";
        delete first_condition;
        delete second_condition;
        delete expr;
    }

    virtual void print(std::ostream &out) const override {
        out << "For(";
        out << "Id: " << id << " ";
        out << "First_condition: ";
        if(first_condition != nullptr)
            first_condition->print(out);
        else
            out << "null ";
        out << "Second_condition: ";
        if(second_condition != nullptr)
            second_condition->print(out);
        else
            out << "null ";
        out << "Expr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }

private:
    std::string id;
    Expr* first_condition;
    Expr* second_condition;
    Expr* expr;

};

#endif