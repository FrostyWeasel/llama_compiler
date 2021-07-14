#ifndef __CONSTANTENTRY_HPP__
#define __CONSTANTENTRY_HPP__

#include "enums.hpp"
#include "type.hpp"
#include "symbol_entry.hpp"

// template <class T>
class ConstantEntry: public SymbolEntry{
public:

   ConstantEntry(std::string id, EntryType entry_type, Type* type) : type(type),
      SymbolEntry(id, entry_type) { }

   ~ConstantEntry() { }

   Type* get_type() { return this->type; }

private:
   Type*         type;                  
   // T*            value;                
};

#endif