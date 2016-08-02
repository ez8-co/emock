
#include <stdlib.h>

#include <mockcpp/DieStub.h>


MOCKCPP_NS_START

/////////////////////////////////////////////////
DieStub::DieStub(int exitCode)
   : code(exitCode)
{
}

/////////////////////////////////////////////////
bool DieStub::isCompleted() const
{
	return false;
}

/////////////////////////////////////////////////
Any& DieStub::invoke(void)
{
   ::exit(code);

   return getEmptyAny();
}

/////////////////////////////////////////////////
std::string DieStub::toString() const
{
   oss_t oss;

   oss << "die(" << code << ")";

   return oss.str();
}

/////////////////////////////////////////////////
const std::type_info& DieStub::type() const
{
   return typeid(void);
}

MOCKCPP_NS_END

