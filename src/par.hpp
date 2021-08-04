#ifndef __PAR_HPP__
#define __PAR_HPP__

#include "ast.hpp"
#include "enums.hpp"
#include <string>
#include <memory>

class Par : public AST{
public:
    Par(std::string* id);
    Par(std::string* id, std::shared_ptr<TypeVariable> type_variable);

    virtual ~Par() {}

    virtual void print(std::ostream &out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;
    virtual void set_type(std::shared_ptr<TypeVariable> type_variable);
    virtual std::shared_ptr<TypeVariable> get_type();

    virtual void sem() override;
    
    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
    std::shared_ptr<TypeVariable> type_variable;
};

#endif