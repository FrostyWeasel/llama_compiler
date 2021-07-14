#include "enums.hpp"
#include "type.hpp"
#include "constraint.hpp"
#include <vector>

class Environment {
public:
    Environment() {  }
    ~Environment() {  }

    inline void add_contraint(Type* t1, Type* t2) {
        contraints.push_back(Constraint(t1, t2));
    }

    void unify();

private:
    std::vector<Constraint> contraints;
};
