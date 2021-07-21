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

        this->type_variable = id_entry->get_type();

        return id_entry->get_type();
    }

    virtual void sem() override {

    }

    virtual llvm::Value* codegen() const override {
        auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);
        auto allocation = id_entry->get_allocation();

        return Builder.CreateLoad(allocation->getAllocatedType(), allocation, id);
    }

private:
    std::string id;
    
};

#endif