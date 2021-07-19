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
    Par(std::string* id): id(*id), type_variable(std::make_shared<TypeVariable>()), AST(NodeType::Par) {}
    Par(std::string* id, std::shared_ptr<TypeVariable> type_variable): id(*id), type_variable(type_variable), AST(NodeType::Par) {  }

    ~Par() {}

    virtual void print(std::ostream &out) const override { 
        out << "(" << id << " :";
        if(type_variable != nullptr)
            type_variable->print(out);
        else
            out << " null";
        out << ")";
    }

    virtual std::shared_ptr<TypeVariable> infer() override {
        ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type_variable);

        st->insert_entry(entry);

        return this->type_variable;
    }

    virtual void set_type(std::shared_ptr<TypeVariable> type_variable) { this->type_variable = type_variable; }
    virtual std::shared_ptr<TypeVariable> get_type() { return this->type_variable; }

    virtual void sem() override {
        ParameterEntry* entry = new ParameterEntry(id, EntryType::ENTRY_PARAMETER, this->type_variable);

        st->insert_entry(entry);

        switch(this->type_variable->get_tag()) {
            case TypeTag::Function : {
                auto to_type = this->type_variable->get_function_to_type();
                if((sa->is_same_tag(to_type, TypeTag::Function))) {
                    std::cerr << "Function " << id << " return type can not be of type function\n" << "offending type is: " << *to_type;
                    exit(1); //TODO: Error handling.
                }
            }
            break;
            default:

            break;
        }
    }

private:
    std::string id;
    std::shared_ptr<TypeVariable> type_variable;
};

#endif