#ifndef __NEW_HPP__
#define __NEW_HPP__

#include "expr.hpp"
#include "includes.hpp"


class New : public Expr{
public:
    New(Type* type): type(type) {}

    virtual void print(std::ostream &out) const override {
        out << "New(";
        out << "Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << ") ";
    }

private:
    Type* type;
};

#endif