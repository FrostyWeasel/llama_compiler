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

//TODO: Search ST for type
class Id : public Expr{
public:
    Id(std::string* id): id(*id) {}

    // std::string get_id() { return id; }

    virtual void print(std::ostream& out) const override{
        out << " " << id;
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);

        return id_entry->get_type();
    }

private:
    std::string id;
    
};

#endif