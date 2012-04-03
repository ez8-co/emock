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

#ifndef __MOCKCPP_MOCK_OBJECT_BASE_H
#define __MOCKCPP_MOCK_OBJECT_BASE_H

#include <typeinfo>

#include <mockcpp/mockcpp.h>
#include <mockcpp/ChainableMockObjectBase.h>
#include <mockcpp/InvocationMockBuilderGetter.h>

MOCKCPP_NS_START

struct MockObjectBaseImpl;

struct MockObjectBase : public ChainableMockObjectBase
{
   ~MockObjectBase();

   virtual void reset();
   virtual void verify();

protected:

   MockObjectBase( const std::string& objName
                 , unsigned int numberOfVptr
                 , const std::type_info& info);

   MockObjectBase(const MockObjectBase&);

protected:

   InvocationMockBuilderGetter
   createInvocationMockerBuilderGetter(const std::string& name, \
          void* addr, unsigned int vptrIndex, unsigned int vtblIndex);
   
   void* toPointerToInterface() const;

   void setDestructor(unsigned int vptrIndex, unsigned int vtblIndex);

   void expectsBeingDeleted();
   void expectsKeepAlive();

private:

   MockObjectBase& operator=(const MockObjectBase&);

private:

   MockObjectBaseImpl* This;
};

MOCKCPP_NS_END

#endif

