#ifndef __USER_TYPE_HPP__
#define __USER_TYPE_HPP__

#include "enums.hpp"
#include "type.hpp"
#include <memory>

class TypeVariable;

class UserType : public Type {
public:
    UserType(std::string id);

    virtual ~UserType();

    virtual bool contains(std::shared_ptr<TypeVariable> type_variable) override;

    virtual void print(std::ostream &out) const override;

private:
    std::string id;

    friend TypeVariable;
};

#endif