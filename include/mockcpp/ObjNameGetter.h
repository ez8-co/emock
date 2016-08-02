
#ifndef __MOCKCPP_OBJ_NAME_GETTER_H
#define __MOCKCPP_OBJ_NAME_GETTER_H

#include <string>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct ObjectNameGetter
{
    virtual const std::string& getName() const = 0;

    virtual ~ObjectNameGetter() {}
};

MOCKCPP_NS_END

#endif

