/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/
#ifndef __MOCKCPP_MSVC_METHOD_INFO_READER_H
#define __MOCKCPP_MSVC_METHOD_INFO_READER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ReportFailure.h>

MOCKCPP_NS_START

#ifdef MSVC_VMG_ENABLED

struct MsvcVmgMFP
{
   void* m_func_address;
#if 0
   int m_delta;
   int m_vtordisp;
   int m_vtable_index; 
#endif
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
