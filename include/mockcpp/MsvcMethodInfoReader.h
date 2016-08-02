#ifndef __MOCKCPP_MSVC_METHOD_INFO_READER_H
#define __MOCKCPP_MSVC_METHOD_INFO_READER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ReportFailure.h>

MOCKCPP_NS_START

#ifdef MSVC_VMG_ENABLED

struct MsvcVmgMFP
{
   void* m_func_address; 
   int m_delta;
   int m_vtordisp;
   int m_vtable_index; 
};

template <typename Method>
union MsvcMethodUnion
{
   MsvcVmgMFP mfp;
   Method method;
};

///////////////////////////////////////////////
template <typename Method>
void* getAddrOfMethod(Method input)
{
	MsvcMethodUnion<Method> m;
	m.method = input;
	return m.mfp.m_func_address;
}

///////////////////////////////////////////////////////////

#else

// TODO
template <typename Method>
void* getAddrOfMethod(Method input)
{
   MOCKCPP_REPORT_FAILURE("please add /D MSVC_VMG_ENABLED and /vmg to your compiler option");
	return 0;
}

///////////////////////////////////////////////////////////
// TODO
template <typename C, typename Method>
unsigned int getIndexOfMethod(Method method)
{
   MOCKCPP_REPORT_FAILURE("please add /D MSVC_VMG_ENABLED and /vmg to your compiler option");
	return 0;
}

///////////////////////////////////////////////////////////
// TODO
template <typename C, typename Method>
unsigned int getDeltaOfMethod(Method method)
{
   MOCKCPP_REPORT_FAILURE("please add /D MSVC_VMG_ENABLED and /vmg to your compiler option");
	return 0;
}
#endif

MOCKCPP_NS_END

#endif
