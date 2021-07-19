#ifndef __FUNCTIONCALL_HPP__
#define __FUNCTIONCALL_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "function_entry.hpp"
#include "parameter_entry.hpp"
#include "enums.hpp"
#include "block.hpp"

class FunctionCall : public Expr{
public:
    FunctionCall(std::string* id, Block<Expr>* expr_list) : id(*id), expr_list(expr_list), Expr(new TypeVariable()) { }

    ~FunctionCall()  {}

    virtual void print(std::ostream &out) const override{
        out << "FunctionCall(";
        out << " Id: " << id << ", ";
        out << "Type: ";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << "null ";
        out << "Expr_list: ";
        if(expr_list != nullptr)
            expr_list->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto entry = this->st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);
        
        std::shared_ptr<TypeVariable> func_type = entry->get_type();
        std::shared_ptr<TypeVariable> par_list_type = this->expr_list->infer();
        std::shared_ptr<TypeVariable> correct_type = std::make_shared<TypeVariable>(TypeTag::Function, par_list_type, this->type_variable); 

        this->st->add_constraint(func_type, correct_type);

        return this->type_variable;
    }

    virtual void sem() override {     
           
        this->expr_list->sem();

    }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif