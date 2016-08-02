
#include <string.h>
#include <mockcpp/IsStringEndWith.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////
bool
IsStringEndWith::predict( const std::string& input
                        , const std::string& target) const
{
    return !::strncmp( input.c_str() - target.size() + input.size()
                     , target.c_str(), target.size());
}

//////////////////////////////////////////////////////////////////
std::string
IsStringEndWith::toString(const std::string& target) const
{
    oss_t oss;
    oss << "endWith(\"" << target << "\")";
    return oss.str();
}

//////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

