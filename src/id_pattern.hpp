#ifndef __ID_PATTERN_HPP__
#define __ID_PATTERN_HPP__

#include "pattern.hpp"
#include <string>
#include <memory>

class TypeVariable;

class IdPattern : public Pattern {
public:
    IdPattern(std::string* id);

    virtual ~IdPattern() {
        
    }

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

    virtual std::string get_id() override { return this->id; }

private:
    std::string id;
};

#endif