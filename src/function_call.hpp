#ifndef __FUNCTIONCALL_HPP__
#define __FUNCTIONCALL_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"
#include "function_entry.hpp"
#include "parameter_entry.hpp"


class FunctionCall : public Expr{
public:
    FunctionCall(std::string* id, Block<Expr>* expr_list) : id(*id), expr_list(expr_list), Expr(new Type(TypeTag::Unknown, this)) { }

    ~FunctionCall() {
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

    virtual Type* infer() override {
        auto entry = this->st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);

        // parameter can be a function if i make a call with it this case is wrong : let twice f x = f (f x)
        switch (entry->get_entry_type()) {
            case EntryType::ENTRY_FUNCTION: {
                FunctionEntry* func_entry = dynamic_cast<FunctionEntry*>(entry);

                Type* from_type = func_entry->get_from_type();
                Type* to_type = func_entry->get_to_type();

                Type* par_list_type = this->expr_list->infer();

                this->st->add_constraint(from_type, par_list_type);
                this->st->add_constraint(to_type, this->type);

                return this->type;
                break;
            }
            case EntryType::ENTRY_PARAMETER: {
                //Found in all scopes. Can be a parameter from a parent function. 
                ParameterEntry* par_entry = dynamic_cast<ParameterEntry*>(entry);
                
                Type* func_type = par_entry->get_type();
                Type* par_list_type = this->expr_list->infer();
                Type* correct_type = new FunctionType(par_list_type, this->type, this); 

                this->st->add_constraint(func_type, correct_type);

                return this->type;
                break;
            }
            
            default:
                std::cerr << "Function call but id " << id << " is not a function or a parameter in current scope.\n";
                exit(1);
                break;
        }
    }

private:
    std::string id;
    Block<Expr>* expr_list;
};

#endif