
#include <mockcpp/CApiHook.h>

MOCKCPP_NS_START

struct CApiHookImpl
{
	CApiHookImpl(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	~CApiHookImpl();
};


/////////////////////////////////////////////////////////////////
CApiHookImpl::CApiHookImpl(CApiHook::Address pfnOld, CApiHook::Address pfnNew )
{
}

/////////////////////////////////////////////////////////////////
CApiHookImpl::~CApiHookImpl()
{
}

/////////////////////////////////////////////////////////////////
CApiHook::CApiHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew)
   : This(new CApiHookImpl(pfnOld, pfnNew))
{
}

/////////////////////////////////////////////////////////////////
CApiHook::~CApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

