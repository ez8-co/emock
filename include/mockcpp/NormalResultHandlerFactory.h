
#ifndef __MOCKCPP_NORMAL_RESULT_HANDLER_FACTORY_H
#define __MOCKCPP_NORMAL_RESULT_HANDLER_FACTORY_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ResultHandlerFactory.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
struct NormalResultHandlerFactory
   : public ResultHandlerFactory
{
    ResultHandler* create(
            bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber);
};

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

