
#include <mockcpp/types/Any.h>

#include <mockcpp/MismatchResultHandler.h>
#include <mockcpp/SelfDescribe.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
MismatchResultHandler::MismatchResultHandler(
                           bool castable
                         , const std::type_info& info
                         , const std::string& typeString
                         , const SelfDescribe* selfDescriber)
           : isCastable(castable)
			  , expectedTypeInfo(info)
			  , expectedTypeString(typeString)
			  , resultProvider(selfDescriber)
{
}

////////////////////////////////////////////////////////////////
bool MismatchResultHandler::matches(const Any& result) const
{
      return !isCastable;
}

////////////////////////////////////////////////////////////////
const Any& MismatchResultHandler::getResult(const Any& result) const
{
    oss_t oss;

    oss << "Returned type does NOT match the method declaration \n"
        << "Required : " << expectedTypeString << "\n"
        << "Returned : " << result.toTypeString() << ", which is from\n"
        << resultProvider->toString();

    MOCKCPP_ASSERT_FALSE_MESSAGE(oss.str(), matches(result));

    return getEmptyAny();
}

MOCKCPP_NS_END

