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
    virtual TypeVariable* infer() { };
    virtual void sem() { };

    void unify() { st->unify(); }

    virtual NodeType get_node_type() { return node_type; }

protected:
    static SymbolTable* st;
    NodeType node_type;
};

inline std::ostream& operator<<(std::ostream& out, const AST& ast){
    ast.print(out);
    return out;
}

#endif