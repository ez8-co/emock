
#ifndef __MOCKCPP_SIMPLE_INVOCATION_RECORDER_H
#define __MOCKCPP_SIMPLE_INVOCATION_RECORDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/InvokedTimesRecorder.h>

MOCKCPP_NS_START

struct SimpleInvocationRecorder
      : public InvokedTimesRecorder
{
    SimpleInvocationRecorder();

    unsigned int getInvokedTimes() const;

    void increaseInvoked();

protected:

    unsigned int invokedTimes;
};

MOCKCPP_NS_END

#endif

