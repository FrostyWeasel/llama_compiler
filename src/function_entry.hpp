#ifndef __FUNCTIONENTRY_HPP__
#define __FUNCTIONENTRY_HPP__

#include "symbol_entry.hpp"
#include "function_type.hpp"
#include "enums.hpp"


class FunctionEntry : public SymbolEntry{
public:

    FunctionEntry(std::string id, EntryType entry_type, TypeVariable* from_type, TypeVariable* to_type) : from_type(from_type), to_type(to_type),
        SymbolEntry(id, entry_type) { count = FunctionEntry::counter++; }
    
    ~FunctionEntry() { }

    void set_from_type(TypeVariable* from_type) { this->from_type = from_type; }
    void set_to_type(TypeVariable* to_type) { this->to_type = to_type; }

    TypeVariable* get_from_type() { return this->from_type; }
    TypeVariable* get_to_type() { return this->to_type; }

    virtual TypeVariable* get_type() const override { return new TypeVariable(TypeTag::Function, this->from_type, this->to_type); }

private:
    TypeVariable*       from_type;
    TypeVariable*       to_type;
    unsigned int        count;
    static unsigned int counter;    /* Μοναδικός για κάθε συνάρτηση, για να ξεχωρίζουμε αυτές που έχουν το ίδιο όνομα */
};

#endif