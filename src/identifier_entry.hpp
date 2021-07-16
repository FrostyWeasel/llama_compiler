#ifndef __IDENTIFIERENTRY_HPP__
#define __IDENTIFIERENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"


class IdentifierEntry: public SymbolEntry {
public:

    IdentifierEntry(std::string id, EntryType entry_type, TypeVariable* type) : type(type),
        SymbolEntry(id, entry_type) { }

    ~IdentifierEntry() { }

    virtual TypeVariable* get_type() const override { return this->type; }

private:
    TypeVariable* type;

};

#endif