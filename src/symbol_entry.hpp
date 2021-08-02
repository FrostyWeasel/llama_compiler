#ifndef __SYMBOLENTRY_HPP__
#define __SYMBOLENTRY_HPP__

#include "scope.hpp"
#include "enums.hpp"
#include "type_variable.hpp"
#include <string>
#include <llvm/IR/Instructions.h>

//Forward Declaration
class Scope;
class TypeVariable;

class SymbolEntry {
public:

   SymbolEntry(std::string id, EntryType entry_type) : id(id), entry_type(entry_type) { }

   virtual ~SymbolEntry() { }

   unsigned int get_hash_value() { return hash_value; }
   void set_hash_value(unsigned int hash_value) { this->hash_value = hash_value; }

   SymbolEntry* get_next_in_scope() { return next_in_scope; }
   void set_next_in_scope(SymbolEntry* next_in_scope) { this->next_in_scope = next_in_scope; }

   SymbolEntry* get_next_hash() { return next_hash; }
   void set_next_hash(SymbolEntry* next_hash) { this->next_hash = next_hash; }

   std::string get_id() { return id; }
   void set_id(std::string id) { this->id = id; }

   unsigned int get_nesting_level() { return nesting_level; }
   void set_nesting_level(unsigned int nesting_level) { this->nesting_level = nesting_level; }

   EntryType get_entry_type() { return this->entry_type; }

   void set_scope(Scope* scope) { this->scope = scope; }
   Scope* get_scope() { return this->scope; }

   llvm::AllocaInst* get_allocation() { return allocation; }
   void set_allocation(llvm::AllocaInst* allocation) { this->allocation = allocation; }

   virtual std::shared_ptr<TypeVariable> get_type() const = 0;

protected:
   std::string         id;                   /* Ονομα αναγνωριστικού          */
   EntryType           entry_type;           /* Τύπος της εγγραφής            */
   llvm::AllocaInst*   allocation;           /* Ptr to variable in stack      */ 

private:
   unsigned int        nesting_level;        /* Βάθος φωλιάσματος             */
   unsigned int        hash_value;           /* Τιμή κατακερματισμού          */
   SymbolEntry*        next_hash;            /* Επόμενη εγγραφή στον Π.Κ.     */
   SymbolEntry*        next_in_scope;        /* Επόμενη εγγραφή στην εμβέλεια */
   Scope*              scope;                /* Εμβέλεια όπου βρίσκεται       */

};

#endif
