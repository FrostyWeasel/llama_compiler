#ifndef __PARAMETERENTRY_HPP__
#define __PARAMETERENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"
class ParameterEntry: public SymbolEntry{
public:

    ParameterEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type) : type(type),
        SymbolEntry(id, entry_type) { }

    virtual ~ParameterEntry() { }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return type; }

private:
    std::shared_ptr<TypeVariable> type;  
 
};

#endif