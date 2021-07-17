#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include "symbol_table.hpp"
#include "type.hpp"
#include "enums.hpp"

class Type;

class AST{
public:

    AST() = default;
    AST(NodeType node_type) : node_type(node_type) { }
    virtual ~AST() { }
    virtual void print(std::ostream& out) const = 0;
    virtual std::shared_ptr<TypeVariable> infer() { };
    virtual void sem() { };

    void unify() { st->unify(); }
    void add_library_functions();
    void close_library_function_scope();

    virtual NodeType get_node_type() { return node_type; }

    virtual void add_to_symbol_table() { }


protected:
    static SymbolTable* st;
    NodeType node_type;

private:
    static unsigned int tab_level;
};

inline std::ostream& operator<<(std::ostream& out, const AST& ast){
    ast.print(out);
    return out;
}

#endif