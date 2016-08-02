
#include <mockcpp/IgnoreResultHandler.h>
#include <mockcpp/Ignore.h>
#include <mockcpp/types/Any.h>
#include <mockcpp/types/AnyCast.h>

MOCKCPP_NS_START

bool IgnoreResultHandler::matches(const Any& val) const
{
   return any_castable<Ignore>(val);
}

const Any& IgnoreResultHandler::getResult(const Any& val) const
{
	return val;
}

MOCKCPP_NS_END

