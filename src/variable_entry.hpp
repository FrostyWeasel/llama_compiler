#ifndef __VARIABLEENTRY_HPP__
#define __VARIABLEENTRY_HPP__

#include "symbol_entry.hpp"
#include "type.hpp"
#include "enums.hpp"


class VariableEntry: public SymbolEntry{
public:

    VariableEntry(std::string id, EntryType entry_type, Type* type) : type(type),
        SymbolEntry(id, entry_type) { }


private:
   Type*         type;                  
   // int           offset;                
};

#endif