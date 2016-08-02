
#include <mockcpp/mockcpp.h>

#include <mockcpp/HookMockObject.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/ApiHookKey.h>
#include <mockcpp/ReportFailure.h>
#include <mockcpp/ApiHookHolder.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
struct HookMockObjectImpl
{
   HookMockObjectImpl(ChainableMockMethodContainer* c)
      : container(c)
   {}

   ChainableMockMethodCore*
   getMethod( const std::string& name
            , const void* api
            , ApiHookHolder* hookHolder
            , InvocationMockerNamespace* ns);
   
   ChainableMockMethodCore*
   getMethod(const void* api);
   
   void reset();

   ChainableMockMethodContainer* container;

private:

   ChainableMockMethodCore* 
   addMethod( const std::string& name
            , const void* api
	    , ApiHookHolder* hookHolder
	    , InvocationMockerNamespace* ns); 

};

//////////////////////////////////////////////////////////////
void
HookMockObjectImpl::reset()
{
    container->reset();
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
HookMockObjectImpl::
addMethod( const std::string& name 
         , const void* api
	 , ApiHookHolder* hookHolder
	 , InvocationMockerNamespace* ns) 
{
    ApiHookKey* key = new ApiHookKey(api, hookHolder);
    ChainableMockMethodCore* method = new ChainableMockMethodCore(name, ns);

    container->addMethod(key, method);

    return method;
}
//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
HookMockObjectImpl::
getMethod(const std::string& name, const void* api
         , ApiHookHolder* hookHolder
         , InvocationMockerNamespace* ns)
{
    ChainableMockMethodCore* method = getMethod(api);
    if (method != 0)
    {
      delete hookHolder;
      return method;
    }

    return addMethod(name, api, hookHolder, ns);
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
HookMockObjectImpl::
getMethod(const void* api) 
{
    ApiHookKey key(api);
    return container->getMethod(&key);
}

//////////////////////////////////////////////////////////////
HookMockObject::HookMockObject(const std::string& name)
   : ChainableMockObjectBase(name)
{
   This = new HookMockObjectImpl(this->getMethodContainer());
}

//////////////////////////////////////////////////////////////
HookMockObject::~HookMockObject()
{
   delete This;
}

//////////////////////////////////////////////////////////////
InvocationMockBuilderGetter
HookMockObject::method(const std::string& name, const void* api, ApiHookHolder* hookHolder)
{
    ChainableMockMethodCore* core = This->getMethod(name, api, hookHolder, this);
    return InvocationMockBuilderGetter(core, core);
}

//////////////////////////////////////////////////////////////
// Private
Invokable*
HookMockObject::getInvokable(const void* api) 
{
   ChainableMockMethodCore* method = This->getMethod(api);
   MOCKCPP_ASSERT_TRUE(
	   "mockcpp internal error (3001): unable to get api pointer",
	   method != 0);
   return method;
}

//////////////////////////////////////////////////////////////
void HookMockObject::reset()
{
   This->reset();
}

//////////////////////////////////////////////////////////////

MOCKCPP_NS_END


