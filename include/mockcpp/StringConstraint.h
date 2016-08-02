
#ifndef __MOCKCPP_STRING_CONSTRAINT_H
#define __MOCKCPP_STRING_CONSTRAINT_H

#include <string>
#include <mockcpp/Constraint.h>

MOCKCPP_NS_START

struct StringPredict;

struct StringConstraint: public Constraint
{
    StringConstraint(const std::string& s, StringPredict* pred);
    ~StringConstraint();

    bool eval(const RefAny& val) const;

    std::string toString() const;

private:
   std::string str;
   StringPredict* predict;
};

MOCKCPP_NS_END

#endif


