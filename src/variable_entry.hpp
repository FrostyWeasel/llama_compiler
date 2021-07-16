#ifndef __VARIABLEENTRY_HPP__
#define __VARIABLEENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"


class VariableEntry: public SymbolEntry {
public:

    VariableEntry(std::string id, EntryType entry_type, TypeVariable* type) : type(type),
        SymbolEntry(id, entry_type) { }
    
    ~VariableEntry() { }

    virtual TypeVariable* get_type() const override { return this->type; }

private:
    TypeVariable* type;                  
};

#endif