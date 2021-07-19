#ifndef __FORDOWNTO_HPP__
#define __FORDOWNTO_HPP__

#include "for.hpp"

class ForDownTo : public For{
public:
    ForDownTo(std::string* id, Expr* first_condition, Expr* second_condition, Expr* expr): For(id, first_condition, second_condition, expr) {}


    virtual void print(std::ostream &out) const override {
        out << "for " << id << " =";

        if(first_condition != nullptr)
            first_condition->print(out);
        else
            out << " null";

        out << " downto";

        if(second_condition != nullptr)
            second_condition->print(out);
        else
            out << " null";

        out << " do";

        if(expr != nullptr)
            expr->print(out);
        else
            out << " null";

        out << " done";
    }

};

#endif