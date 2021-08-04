#ifndef __CONSTRUCTOR_PATTERN_HPP__
#define __CONSTRUCTOR_PATTERN_HPP__

#include "pattern.hpp"
#include "block.hpp"
#include <string>
#include <memory>

class TypeVariable;

class ConstructorPattern : public Pattern {
public:
    ConstructorPattern(std::string* id, Block<Pattern>* pattern_list);

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    std::string id;
    Block<Pattern>* pattern_list;
};

#endif