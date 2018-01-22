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

#ifndef __MOCKCPP_VIRTUAL_TABLE_H
#define __MOCKCPP_VIRTUAL_TABLE_H

#include <typeinfo>
#include <string>

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

