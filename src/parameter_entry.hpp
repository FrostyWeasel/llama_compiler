#ifndef __PARAMETERENTRY_HPP__
#define __PARAMETERENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
class ParameterEntry: public SymbolEntry{
public:

    ParameterEntry(std::string id, EntryType entry_type, TypeVariable* type) : type(type),
        SymbolEntry(id, entry_type) { }

    ~ParameterEntry() { }

    virtual TypeVariable* get_type() const override { return type; }

private:
    TypeVariable* type;  
 
};

#endif