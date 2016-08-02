
#ifndef __MOCKCPP_INVOKED_TIMES_READER_H
#define __MOCKCPP_INVOKED_TIMES_READER_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct InvokedTimesReader
{
    virtual ~InvokedTimesReader() {}

    virtual unsigned int getInvokedTimes() const = 0;
};

MOCKCPP_NS_END

#endif

