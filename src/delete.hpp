#ifndef __DELETE_HPP__
#define __DELETE_HPP__

#include "expr.hpp"
#include "includes.hpp"


class Delete : public Expr{
public:
    Delete(Expr* expr): expr(expr) {}

    ~Delete() {
	std::cout << "Delete deleted\n";
        delete expr;
    }

    virtual void print(std::ostream &out) const override {
        out << "Delete(";
        out << "Exr: ";
        if(expr != nullptr)
            expr->print(out);
        else
            out << "null ";
        out << ") ";
    }

private:
    Expr* expr;

};

#endif