
#include <mockcpp/MismatchResultHandlerFactory.h>
#include <mockcpp/MismatchResultHandler.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ResultHandler* MismatchResultHandlerFactory::create(
            bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* resultProvider)
{
    return new MismatchResultHandler(isCastable
                         , expectedTypeInfo
                         , expectedTypeString
                         , resultProvider);
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

