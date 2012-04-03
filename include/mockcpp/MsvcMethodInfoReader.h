/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
