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

    virtual ~Par() {}

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;
    virtual void set_type(std::shared_ptr<TypeVariable> type_variable);
    virtual std::shared_ptr<TypeVariable> get_type();

    virtual void sem() override;
    
    virtual llvm::Value* codegen() override;

    virtual std::string get_id();

private:
    std::string id;
    std::shared_ptr<TypeVariable> type_variable;
};

#endif