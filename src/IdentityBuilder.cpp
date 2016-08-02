
#include <mockcpp/IdentityBuilder.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/InvocationId.h>

MOCKCPP_NS_START

void IdentityBuilder::id(const std::string& id)
{
	getMocker()->setId(new InvocationId(id));
}


MOCKCPP_NS_END


