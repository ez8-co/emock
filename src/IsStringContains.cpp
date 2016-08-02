
#include <mockcpp/IsStringContains.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
bool
IsStringContains::predict(const std::string& input
               , const std::string& target) const
{
   const char* s = input.c_str();
   int len = input.size() - target.size() + 1;
   for(int i=0; i < len; i++)
   {
      if(!::strncmp(&s[i], target.c_str(), target.size()))
      {
         return true;
      }
   }

   return false;
}

///////////////////////////////////////////////////////////
std::string
IsStringContains::toString(const std::string& target) const
{
    oss_t oss;
    oss << "contains(\"" << target << "\")";
    return oss.str();
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

