
#ifndef __MOCKCPP_RESULT_HANDLER_FACTORY_H
#define __MOCKCPP_RESULT_HANDLER_FACTORY_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

struct Any;
struct SelfDescribe;
struct ResultHandler;
struct ResultImpl;

struct ResultHandlerFactory
{
    virtual ResultHandler* create(
            bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber) = 0;

    virtual ~ResultHandlerFactory() {}
};

MOCKCPP_NS_END

#endif

