#ifndef __NEW_HPP__
#define __NEW_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"

class New : public Expr{
public:
    New(std::shared_ptr<TypeVariable> type_variable): new_type_variable(type_variable), Expr(new TypeVariable(TypeTag::Reference, type_variable)) { }

    virtual void print(std::ostream &out) const override {
        out << " new";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        return this->type_variable;
    }

    virtual void sem() override {
        if((sa->is_same_tag(this->new_type_variable, TypeTag::Array))) {
            std::cerr << "New expression type can not be of type array\n" << "offending type is: " << *this->new_type_variable;
            exit(1); //TODO: Error handling.
        }
    }

private:
    std::shared_ptr<TypeVariable> new_type_variable;
};

#endif