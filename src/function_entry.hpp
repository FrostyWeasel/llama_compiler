#ifndef __FUNCTIONENTRY_HPP__
#define __FUNCTIONENTRY_HPP__

#include "includes.hpp"
#include "symbol_entry.hpp"

class FunctionEntry: public SymbolEntry{
public:

    FunctionEntry(std::string id, EntryType entry_type, unsigned int nesting_level, unsigned int hash_value,
        SymbolEntry* next_hash, SymbolEntry* next_in_scope, Scope* scope, FunctionType* type) : type(type), 
        SymbolEntry(id, entry_type, nesting_level, hash_value, next_hash, next_in_scope, scope) { this->counter++; }
    
    ~FunctionEntry() { }

private:
    // bool                isForward;
    // SymbolEntry*        firstArgument;
    // SymbolEntry*        lastArgument;
    // Type*               resultType;
    FunctionType*       type;
    // ParDef              pardef;
    static unsigned int counter;    /* Μοναδικός για κάθε συνάρτηση, για να ξεχωρίζουμε αυτές που έχουν το ίδιο όνομα */
};

#endif