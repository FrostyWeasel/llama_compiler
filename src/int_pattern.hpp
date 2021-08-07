#ifndef __INT_PATTERN_HPP__
#define __INT_PATTERN_HPP__

#include "pattern.hpp"
#include <string>
#include <memory>

class TypeVariable;

class IntPattern : public Pattern {
public:
    IntPattern(int value);

    virtual ~IntPattern() {
        
    }

    virtual void print(std::ostream& out) const override;

    virtual std::shared_ptr<TypeVariable> infer() override;

    virtual void sem() override;

    virtual llvm::Value* codegen() override;

private:
    int value;
};

#endif