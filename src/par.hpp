#ifndef __PAR_HPP__
#define __PAR_HPP__

#include "ast.hpp"
#include "type.hpp"
#include "enums.hpp"
#include "symbol_entry.hpp"
#include "parameter_entry.hpp"
#include <string>

class Par : public AST{
public:
    Par(std::string* id): id(*id), type(new Type(TypeTag::Unknown, this)), AST(NodeType::Par) {}
    Par(std::string* id, Type* type): id(*id), type(type), AST(NodeType::Par) { type->set_parent(this); }

    ~Par() {
        delete type;
    }

    virtual void print(std::ostream &out) const override { 
        out << "Par(";
        out << "Id: " << id << " ";
        out << "Type: ";
        if(type != nullptr)
            type->print(out);
        else
            out << "null ";
        out << ") ";
    }

    virtual Type* infer() override {
        ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type);

        st->insert_entry(entry);

        return this->type;
    }

    virtual void set_type(Type* type) { this->type = type; }

private:
    std::string id;
    Type* type;
};

#endif