
#ifndef __MOCKPP_PLACEHOLDER_H
#define __MOCKPP_PLACEHOLDER_H

#include <typeinfo>
#include <string>

#include <mockcpp/mockcpp.h>
#include <mockcpp/IsAnythingHelper.h>

MOCKCPP_NS_START

struct Constraint;

struct PlaceHolder
{
    virtual ~PlaceHolder() {}
    virtual const std::type_info & type() const = 0;
    virtual PlaceHolder* clone() const = 0;
    virtual std::string toString(void) const = 0;
    virtual std::string toTypeString(void) const = 0;
    virtual std::string toTypeAndValueString(void) const = 0;
    virtual Constraint* getConstraint() const { return 0; }
};

MOCKCPP_NS_END


#endif // __MOCKPP_PLACEHOLDER_H


