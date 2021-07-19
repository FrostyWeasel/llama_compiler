#ifndef __VARIABLEENTRY_HPP__
#define __VARIABLEENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"


class VariableEntry: public SymbolEntry {
public:

    VariableEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type) : type(type),
        dim(0), SymbolEntry(id, entry_type) { }
    
    VariableEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type, unsigned int dim) : type(type),
        dim(dim), SymbolEntry(id, entry_type) { }
    
    virtual ~VariableEntry() { }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return this->type; }
    unsigned int get_dim() { return dim; }

private:
    std::shared_ptr<TypeVariable> type;   
    unsigned int dim;               
};

#endif