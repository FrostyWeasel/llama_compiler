#ifndef __VARIABLEENTRY_HPP__
#define __VARIABLEENTRY_HPP__

#include "includes.hpp"
#include "symbol_entry.hpp"

class VariableEntry: public SymbolEntry{
public:

    VariableEntry(std::string id, EntryType entry_type, unsigned int nesting_level, unsigned int hash_value,
        SymbolEntry* next_hash, SymbolEntry* next_in_scope, Scope* scope, Type* type) : type(type),
        SymbolEntry(id, entry_type, nesting_level, hash_value, next_hash, next_in_scope, scope) { }


private:
   Type*         type;                  
   // int           offset;                
};

#endif