
#include <mockcpp/types/Any.h>
#include <mockcpp/types/AnyCast.h>

#include <mockcpp/Void.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/VoidResultHandler.h>
#include <mockcpp/SelfDescribe.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////
VoidResultHandler::VoidResultHandler(
                   const std::type_info& typeInfo
                 , const std::string& typeString
                 , const SelfDescribe* selfDescriber)
           : expectedTypeInfo(typeInfo)
           , expectedTypeString(typeString)
           , resultProvider(selfDescriber)
{
}

/////////////////////////////////////////////////////////
bool VoidResultHandler::matches(const Any& result) const
{
    return expectedTypeInfo != typeid(void) && any_castable<Void>(result);
}

/////////////////////////////////////////////////////////
const Any& VoidResultHandler::getResult(const Any& result) const
{
    oss_t oss;

    oss << "You need to specify a return value by using will(...) in \n"
        << resultProvider->toString() << "\n"
        << "Expected Return Type: " << expectedTypeString << "\n";

    MOCKCPP_FAIL(oss.str());

    return getEmptyAny();
}

/////////////////////////////////////////////////////////

MOCKCPP_NS_END

