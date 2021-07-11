#ifndef __IDENTIFIERENTRY_HPP__
#define __IDENTIFIERENTRY_HPP__

#include "symbol_entry.hpp"
#include "type.hpp"
#include "enums.hpp"


class IdentifierEntry: public SymbolEntry{
public:

    IdentifierEntry(std::string id, EntryType entry_type) : type(type),
        SymbolEntry(id, entry_type) { }

private:
    Type*   type;
};

#endif