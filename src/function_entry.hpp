#ifndef __FUNCTIONENTRY_HPP__
#define __FUNCTIONENTRY_HPP__

#include "symbol_entry.hpp"
#include "function_type.hpp"
#include "enums.hpp"


class FunctionEntry : public SymbolEntry{
public:

    FunctionEntry(std::string id, EntryType entry_type, Type* from_type, Type* to_type) : from_type(from_type), to_type(to_type),
        SymbolEntry(id, entry_type) { this->counter++; }
    
    ~FunctionEntry() { }

    void set_from_type(Type* from_type) { this->from_type = from_type; }
    void set_to_type(Type* to_type) { this->to_type = to_type; }

private:
    Type*               from_type;
    Type*               to_type;
    static unsigned int counter;    /* Μοναδικός για κάθε συνάρτηση, για να ξεχωρίζουμε αυτές που έχουν το ίδιο όνομα */
};

#endif