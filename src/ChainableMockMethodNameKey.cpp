
#include <mockcpp/ChainableMockMethodNameKey.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
ChainableMockMethodNameKey::
ChainableMockMethodNameKey(const std::string& name)
   : methodName(name)
{
}

/////////////////////////////////////////////////////
bool
ChainableMockMethodNameKey::
equals(const ChainableMockMethodKey * const rhs) const
{
   if(rhs == 0)
   {
      return false;
   }

   if(rhs == this)
   {
      return true;
   }

   ChainableMockMethodNameKey* key = \
          dynamic_cast<ChainableMockMethodNameKey*>(
              const_cast<ChainableMockMethodKey*>(rhs));
   if(key == 0)
   {
      return false;
   }
   
   return key->getMethodName() == this->getMethodName();
}

/////////////////////////////////////////////////////
std::string&
ChainableMockMethodNameKey::
getMethodName() const
{
   return const_cast<std::string&>(this->methodName);
}

/////////////////////////////////////////////////////

MOCKCPP_NS_END

