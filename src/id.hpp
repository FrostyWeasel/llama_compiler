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
        out << "Id(" << id << ") ";
    }

    virtual TypeVariable* infer() override {
        auto id_entry = st->lookup_entry(this->id, LookupType::LOOKUP_ALL_SCOPES);

        //TODO: Handle all entry types
        switch (id_entry->get_entry_type()) {
            case EntryType::ENTRY_CONSTANT: {
                ConstantEntry* entry = dynamic_cast<ConstantEntry*>(id_entry);

                return entry->get_type();
                break;
            }
            case EntryType::ENTRY_PARAMETER: {
                ParameterEntry* entry = dynamic_cast<ParameterEntry*>(id_entry);

                return entry->get_type();
            }
            case EntryType::ENTRY_VARIABLE: {
                VariableEntry* entry = dynamic_cast<VariableEntry*>(id_entry);

                return entry->get_type();
            }
            case EntryType::ENTRY_FUNCTION: {
                FunctionEntry* entry = dynamic_cast<FunctionEntry*>(id_entry);

                return entry->get_type();
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