
#include <mockcpp/Functor.h>
#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/utils.h>

MOCKCPP_NS_START

MockObjectType GlobalMockObject::instance("");

void GlobalMockObject::verify()
{
   try
   {
      instance.verify();
   }
   catch(...)
   {
       __RUN_NOTHROW({
           instance.reset();
       });
       throw;
   }

   __RUN_THROW({
       instance.reset();
   });
}

void GlobalMockObject::reset()
{
    instance.reset();
}

MOCKCPP_NS_END

