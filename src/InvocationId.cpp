
#include <mockcpp/InvocationId.h>

MOCKCPP_NS_START


InvocationId::InvocationId(const std::string& identity)
        : id(identity)
{}

std::string InvocationId::getId(void) const
{
    return id;
}

std::string InvocationId::toString(void) const
{
    return std::string(".id(\"") + id + std::string("\")");
}


MOCKCPP_NS_END



