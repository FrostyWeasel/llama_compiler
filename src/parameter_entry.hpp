#ifndef __PARAMETERENTRY_HPP__
#define __PARAMETERENTRY_HPP__

#include "symbol_entry.hpp"
#include "type.hpp"
#include "enums.hpp"


class ParameterEntry: public SymbolEntry{
public:

    ParameterEntry(std::string id, EntryType entry_type, Type* type) : type(type),
        SymbolEntry(id, entry_type) { }

private:
    Type*         type;  
    // int           offset;
    // PassMode      mode;  
    // SymbolEntry*  next;  
};

#endif