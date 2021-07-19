#ifndef __IDENTIFIERENTRY_HPP__
#define __IDENTIFIERENTRY_HPP__

#include "symbol_entry.hpp"
#include "type_variable.hpp"
#include "enums.hpp"


class IdentifierEntry: public SymbolEntry {
public:

    IdentifierEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type) : type(type),
        SymbolEntry(id, entry_type) { }

    virtual ~IdentifierEntry() { }

    virtual std::shared_ptr<TypeVariable> get_type() const override { return this->type; }

private:
    std::shared_ptr<TypeVariable> type;

};

#endif