#ifndef __CONSTANTENTRY_HPP__
#define __CONSTANTENTRY_HPP__

#include "enums.hpp"
#include "type_variable.hpp"
#include "symbol_entry.hpp"

class ConstantEntry: public SymbolEntry {
public:

   ConstantEntry(std::string id, EntryType entry_type, std::shared_ptr<TypeVariable> type) : type(type),
      SymbolEntry(id, entry_type) { }

   virtual ~ConstantEntry() { }

   virtual std::shared_ptr<TypeVariable> get_type() const override { return this->type; }

private:
   std::shared_ptr<TypeVariable> type;                  
   // T*            value;                
};

#endif