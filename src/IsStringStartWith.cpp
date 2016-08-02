
#include <mockcpp/IsStringStartWith.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////////
bool
IsStringStartWith::predict(const std::string& input,
                           const std::string& target) const 
{
   return !::strncmp(input.c_str(), target.c_str(), target.size());
}

////////////////////////////////////////////////////////////////////
std::string
IsStringStartWith::toString(const std::string& target) const
{
    oss_t oss;

    oss << "startWith(\"" << target << "\")";

    return oss.str();
}

MOCKCPP_NS_END

