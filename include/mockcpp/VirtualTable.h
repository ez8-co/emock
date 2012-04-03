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

#ifndef __MOCKCPP_VIRTUAL_TABLE_H
#define __MOCKCPP_VIRTUAL_TABLE_H

#include <typeinfo>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct ObjectNameGetter;
struct IndexInvokableGetter;
struct VirtualTableImpl;

struct VirtualTable
{
   VirtualTable( IndexInvokableGetter* getter
               , ObjectNameGetter* nameGetter
               , unsigned int numberOfVptr
               , const std::type_info&);

   ~VirtualTable();

   void* toPointerToInterface() const;

   void addMethod(void* methodAddr, unsigned int indexOfVtbl, unsigned int indexofVptr = 0);
   void setDestructor(unsigned int vptrIndex, unsigned int vtblIndex);

   void expectsBeingDeleted();
   void expectsKeepAlive();

   void verify();
   void reset();

   static IndexInvokableGetter* getInvokableGetter(void* Caller, unsigned int indexOfVptr);

private:
	VirtualTableImpl* This;
};

MOCKCPP_NS_END

#endif

