
#include <mockcpp/ApiHookKey.h>
#include <mockcpp/ApiHook.h>
#include <mockcpp/ApiHookHolder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ApiHookKey::ApiHookKey(const void* api, ApiHookHolder* holder)
   : apiAddress(api)
   , hookHolder(holder)
{
   hook = new ApiHook(api, holder->getApiHook());
}

///////////////////////////////////////////////////////////
ApiHookKey::ApiHookKey(const void* api)
   : apiAddress(api), hook(0), hookHolder(0)
{
}

////////////////////////////////////////////////////////////
ApiHookKey::~ApiHookKey()
{
   delete hook;
   delete hookHolder;
}   

////////////////////////////////////////////////////////////
bool ApiHookKey::equals(
      const ChainableMockMethodKey* const rhs) const
{
    if(rhs == 0)
    {
       return false;
    }

    if(this == rhs)
    {
       return true;
    }

    ApiHookKey* key = \
          dynamic_cast<ApiHookKey*> \
             (const_cast<ChainableMockMethodKey*>(rhs));
    if(key == 0)
    {
       return false;
    }
     
    return key->apiAddress == this->apiAddress;
}

MOCKCPP_NS_END
