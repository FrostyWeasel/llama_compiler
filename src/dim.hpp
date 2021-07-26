#ifndef __DIM_HPP__
#define __DIM_HPP__

#include "expr.hpp"
#include "variable_entry.hpp"
#include "type_variable.hpp"
#include <iostream>
#include <memory>
#include <string>

class Dim : public Expr{
public:
    Dim(std::string* id): id(*id), dimension(1) {}
    Dim(std::string* id, unsigned int dimension): id(*id), dimension(dimension) {}

    virtual void print(std::ostream &out) const override {
        out << " dim " << dimension << " " << id;
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

        SymbolEntry* entry = st->lookup_entry(id, LookupType::LOOKUP_ALL_SCOPES);

        st->add_constraint(entry->get_type(), std::make_shared<TypeVariable>(TypeTag::Array,
            std::make_shared<TypeVariable>(TypeTag::Unknown), this->dimension, DimType::AtLeast));

        return this->type_variable;
    }

    virtual void sem() override {

        //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
        if(this->pass_stage == PassStage::FunctionDef) {
            auto entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
            
            // If id not in the same scope as the parameters of the function
            if(entry->get_nesting_level() != this->st->get_current_nesting_level()) {
                this->current_func_def_non_locals->insert({ this->id, entry->get_type() });
            }
        }   

    }


private:
    std::string id;
    unsigned int dimension;

};

#endif