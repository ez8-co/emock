
#ifndef __MOCKCPP_VOID_RESULT_HANDLER_H
#define __MOCKCPP_VOID_RESULT_HANDLER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ResultHandler.h>

#include <string>
#include <typeinfo>

MOCKCPP_NS_START

struct Any;
struct SelfDescribe;

///////////////////////////////////////////////////////////
struct VoidResultHandler: public ResultHandler
{
    VoidResultHandler( const std::type_info& typeInfo
                     , const std::string& expectedTypeString
                     , const SelfDescribe* resultProvider);

    bool matches(const Any& val) const;

    const Any& getResult(const Any& val) const;

private:

    const std::type_info& expectedTypeInfo;
    const std::string expectedTypeString;
    const SelfDescribe* resultProvider;
};

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

