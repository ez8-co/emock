
#ifndef __MOCKCPP_IDENTITY_BUILDER_H
#define __MOCKCPP_IDENTITY_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

struct InvocationMocker;

struct IdentityBuilder
{
    void id(const std::string& id);

    virtual ~IdentityBuilder() {}

private:
    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#endif

