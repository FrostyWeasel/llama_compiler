#ifndef __NEW_HPP__
#define __NEW_HPP__

#include "expr.hpp"
#include "type_variable.hpp"
#include "enums.hpp"

//TODO: new_type_variable can be int, int->int, int->int->int, int->int ref... and result is reference to type_variable... during inference we only need to check that new_type_variable is not
//TODO: array type and the just use the new_type_variable ref as the result for use in inference.
//TODO: Sem new_type_variable must not be array type

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

private:
    std::shared_ptr<TypeVariable> new_type_variable;
};

#endif