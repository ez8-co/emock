
#ifndef __MOCKCPP_INDEX_INVOKABLE_GETTER_H
#define __MOCKCPP_INDEX_INVOKABLE_GETTER_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct Invokable;

struct IndexInvokableGetter
{
    virtual Invokable* getInvokable(unsigned int indexOfVtbl, \
                                    unsigned int indexOfVptr = 0) const = 0;

    virtual ~IndexInvokableGetter() {}
};

MOCKCPP_NS_END

#endif

