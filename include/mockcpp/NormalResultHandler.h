
#ifndef __MOCKCPP_NORMAL_RESULT_HANDLER_H
#define __MOCKCPP_NORMAL_RESULT_HANDLER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ResultHandler.h>

MOCKCPP_NS_START

struct Any;

struct NormalResultHandler : public ResultHandler
{
    NormalResultHandler(bool castable);

    bool matches(const Any& result) const;

    const Any& getResult(const Any& result) const;

private:

    const bool isCastable;

};

MOCKCPP_NS_END

#endif

