
#ifndef __MOCKCPP_IGNORE_RESULT_HANDLER_H
#define __MOCKCPP_IGNORE_RESULT_HANDLER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ResultHandler.h>

MOCKCPP_NS_START

struct Any;

struct IgnoreResultHandler : public ResultHandler
{
    bool matches(const Any& result) const;

    const Any& getResult(const Any& result) const;
};

MOCKCPP_NS_END

#endif

