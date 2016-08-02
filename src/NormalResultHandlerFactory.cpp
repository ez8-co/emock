
#include <mockcpp/NormalResultHandlerFactory.h>
#include <mockcpp/NormalResultHandler.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ResultHandler* NormalResultHandlerFactory::create(
            bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
{
    return new NormalResultHandler(isCastable);
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

