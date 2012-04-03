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
#ifndef __MOCKCPP_MSVC_RTTI_H_
#define __MOCKCPP_MSVC_RTTI_H_

#ifdef _MSC_VER

#include <typeinfo>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct PMD
{
    int mdisp;  //member displacement
    int pdisp;  //vbtable displacement
    int vdisp;  //displacement inside vbtable
};

struct RTTIBaseClassDescriptor
{
    std::type_info* typeInfo; //type descriptor of the class
    unsigned int numContainedBases; //number of nested classes following in the Base Class Array
    PMD where;        //pointer-to-member displacement info
    unsigned int attributes;        //flags, usually 0
};

struct RTTIClassHierarchyDescriptor
{
    unsigned int signature;      //always zero?
    unsigned int attributes;     //bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
    unsigned int numBaseClasses; //number of classes in pBaseClassArray
    RTTIBaseClassDescriptor** pBaseClassArray;

    RTTIClassHierarchyDescriptor(bool mi = false)
		: signature(0),attributes(mi?1:0),numBaseClasses(0), pBaseClassArray(0)
	{
	}
};

struct RTTICompleteObjectLocator
{
    unsigned int signature; //always zero ?
    unsigned int offset;    //offset of this vtable in the complete class
    unsigned int cdOffset;  //constructor displacement offset
	const std::type_info* typeInfo; //TypeDescriptor of the complete class
    RTTIClassHierarchyDescriptor* pClassDescriptor; //describes inheritance hierarchy

    RTTICompleteObjectLocator(unsigned int index
            , const std::type_info& info, RTTIClassHierarchyDescriptor* desc)
		: signature(0), offset(index*sizeof(void*)), cdOffset(0)
		, typeInfo(&info), pClassDescriptor(desc)
	{}
};

MOCKCPP_NS_END

#endif

#endif
