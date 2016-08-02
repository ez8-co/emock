
#include <mockcpp/IgnoreResultHandlerFactory.h>
#include <mockcpp/IgnoreResultHandler.h>
#include <mockcpp/SelfDescribe.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ResultHandler* IgnoreResultHandlerFactory::create(
            bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
{
    return new IgnoreResultHandler();
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

