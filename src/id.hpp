#ifndef __ID_HPP__
#define __ID_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "symbol_entry.hpp"
#include "constant_entry.hpp"
#include "parameter_entry.hpp"

class Id : public Expr{
public:
    Id(std::string* id): id(*id) {}

    // std::string get_id() { return id; }

    virtual void print(std::ostream& out) const override{
        out << " " << id;
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        this->entry = id_entry;

        this->type_variable = id_entry->get_type();

        return id_entry->get_type();
    }

    virtual void sem() override {
        //* Not part of semantic analysis. Gathering non-local variables in function definition body for use during code generation
        if(this->pass_stage == PassStage::FunctionDef) {
            auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
            
            // If id not in the same scope as the parameters of the function
            if(id_entry->get_nesting_level() != this->st->get_current_nesting_level()) {
                this->current_func_def_non_locals->insert({ this->id, entry->get_type() });
            }
        }
    }

    virtual llvm::Value* codegen() override {
        auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        auto allocation = id_entry->get_allocation();

        if(allocation != nullptr)
            return Builder.CreateLoad(allocation->getAllocatedType(), allocation, id);

        return nullptr;
    }

private:
    std::string id;
    
};

#endif