#ifndef __ID_HPP__
#define __ID_HPP__

#include <iostream>
#include <string>
#include "expr.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "includes.hpp"

//TODO: Search ST for type
class Id : public Expr{
public:
    Id(std::string* id): id(*id) {}

    // std::string get_id() { return id; }

    virtual void print(std::ostream& out) const override{
        out << "Id(" << id << ") ";
    }

    virtual Type* infer() override {
        auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);

        //TODO: Handle all entry types
        switch (id_entry->get_entry_type()) {
            case EntryType::ENTRY_CONSTANT: {
                ConstantEntry* entry = dynamic_cast<ConstantEntry*>(id_entry);
                return entry->get_type();
                break;
            }
            default: {
                //TODO: Error Handling
                std::cerr << "Uknown entry type";
                exit(1);
                break;
            }
        }
    }

private:
    std::string id;
    
};

#endif