
#include <typeinfo>
#include <string.h>

#include <mockcpp/mockcpp.h>

#if defined(_MSC_VER)
#include <mockcpp/MsvcRtti.h>
#endif

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
namespace
{
#if defined(__GNUC__)
   const unsigned int EXTRA_VTBL_SLOT = 2;
#elif defined(_MSC_VER)
   const unsigned int EXTRA_VTBL_SLOT = 1;
#endif
   const unsigned int SLOTS_PER_VTBL = MOCKCPP_MAX_VTBL_SIZE + EXTRA_VTBL_SLOT;

   unsigned int times = 0;
}

///////////////////////////////////////////////////////////////////////
void** createVtbls(unsigned int numberOfVptr)
{
	void **p = new void*[numberOfVptr * SLOTS_PER_VTBL];
	(void)memset(p, 0, sizeof(void *) * numberOfVptr * SLOTS_PER_VTBL);
	return p;
}

void freeVtbls(void** vtbl, unsigned int numberOfVptr)
{
#if defined(_MSC_VER)
	 RTTIClassHierarchyDescriptor* desc = 0;
   for(unsigned int i=0; i<numberOfVptr; i++)
   {
      int base = i*SLOTS_PER_VTBL;
	    if(vtbl[base] != 0)
	    {
	    	  RTTICompleteObjectLocator* rtti = (RTTICompleteObjectLocator*)vtbl[base];
	    	  desc = rtti->pClassDescriptor;
	    	  delete rtti;
	    }
   }
   if(desc != 0)
   {
	    delete desc;
   }
#endif

   delete [] vtbl;
}
///////////////////////////////////////////////////////////////////////
unsigned int getRealVtblIndex(unsigned int indexOfVptr, unsigned int indexOfVtbl)
{
   return indexOfVptr * SLOTS_PER_VTBL + EXTRA_VTBL_SLOT + indexOfVtbl ;
}

///////////////////////////////////////////////////////////////////////
void initializeVtbls(void** vptr, void**vtbl, unsigned int numberOfVptr, const std::type_info& info, bool hasRtti)
{  

#if defined(_MSC_VER)

	RTTIClassHierarchyDescriptor * desc = 0;
	if(hasRtti)
	{
	   desc = new RTTIClassHierarchyDescriptor(numberOfVptr > 1 ? true : false);
	}

#endif

   for(unsigned int i=0; i<numberOfVptr; i++)
   {
      int base = i*SLOTS_PER_VTBL;

#if defined(__GNUC__)
      vtbl[base + 0] = (void*)(-1*(sizeof(void*)*i));
      vtbl[base + 1] = (void*)&info;
#elif defined(_MSC_VER)
	    //FIXME
	    vtbl[base + 0] = hasRtti ? new RTTICompleteObjectLocator(i, info, desc) : 0;
#endif

      vptr[i] = (void*)&vtbl[base + EXTRA_VTBL_SLOT];
   }
}
///////////////////////////////////////////////////////////////////////


MOCKCPP_NS_END
