#ifndef __SCOPE_HPP__
#define __SCOPE_HPP__

#include "symbol_entry.hpp"

//Forward declaration
class SymbolEntry;
class Scope {
public:
    Scope(Scope* parent, SymbolEntry* entries, unsigned int nesting_level, bool is_hidden) : 
        parent(parent), entries(entries), nesting_level(nesting_level), is_hidden(is_hidden) {}

    unsigned int get_nesting_level() { return nesting_level; }
    // void setNestingLevel(unsigned int nesting_level) { this->nesting_level = nesting_level; }

    bool get_hidden() { return is_hidden; }
    void set_is_hidden(bool is_hidden) { this->is_hidden = is_hidden; }

    SymbolEntry* get_entries() { return entries; }
    void set_entries(SymbolEntry* entries) { this->entries = entries; }
    
    Scope* get_parent() { return this->parent; }

private:
    unsigned int    nesting_level;             /* Βάθος φωλιάσματος      */
    // unsigned int    negOffset;                /* Τρέχον αρνητικό offset */
    Scope*          parent;                   /* Περιβάλλουσα εμβέλεια  */
    SymbolEntry*    entries;                  /* Σύμβολα της εμβέλειας  */
    bool            is_hidden;                /* Κρυφή εμβέλεια ή όχι   */

};

#endif
    