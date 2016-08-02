
#ifndef __MOCKCPP_MISMATCH_RESULT_HANDLER_H
#define __MOCKCPP_MISMATCH_RESULT_HANDLER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ResultHandler.h>

MOCKCPP_NS_START

struct Any;
struct SelfDescribe;

struct MismatchResultHandler: public ResultHandler
{
    MismatchResultHandler( bool castable
                         , const std::type_info& expectedTypeInfo
                         , const std::string& expectedTypeString
                         , const SelfDescribe* resultProvider);

    bool matches(const Any& result) const;

    const Any& getResult(const Any& result) const;

private:
    const bool isCastable;
    const std::type_info& expectedTypeInfo;
    const std::string expectedTypeString;
    const SelfDescribe* resultProvider;
};

MOCKCPP_NS_END

#endif

