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

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockObject.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/ChainableMockMethodNameKey.h>
#include <mockcpp/InvocationMockerNamespace.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
struct ChainableMockObjectImpl
{
   ChainableMockObjectImpl(ChainableMockMethodContainer* c)
      : container(c)
   {}

   ChainableMockMethodCore*
   getMethod(const std::string& name, InvocationMockerNamespace* ns);
   
   void reset();

   ChainableMockMethodContainer* container;

private:

   ChainableMockMethodCore* 
   addMethod(const std::string& name, InvocationMockerNamespace* ns); 

};

//////////////////////////////////////////////////////////////
void
ChainableMockObjectImpl::reset()
{
    container->reset();
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObjectImpl::
addMethod(const std::string& name, InvocationMockerNamespace* ns) 
{
    ChainableMockMethodNameKey* key = new ChainableMockMethodNameKey(name);
    ChainableMockMethodCore* method = new ChainableMockMethodCore(name, ns);

    container->addMethod(key, method);

    return method;
}
//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObjectImpl::
getMethod(const std::string& name, InvocationMockerNamespace* ns) 
{
    ChainableMockMethodNameKey key(name);

    ChainableMockMethodCore* method = container->getMethod(&key);
    if (method != 0)
    {
      return method;
    }

    return addMethod(name, ns);
}

//////////////////////////////////////////////////////////////
ChainableMockObject::ChainableMockObject(const std::string& name)
    : ChainableMockObjectBase(name)
{
	This = new ChainableMockObjectImpl(this->getMethodContainer());
}

//////////////////////////////////////////////////////////////
ChainableMockObject::~ChainableMockObject()
{
   delete This;
}

//////////////////////////////////////////////////////////////
InvocationMockBuilderGetter
ChainableMockObject::method(const std::string& name)
{
    ChainableMockMethodCore* core = This->getMethod(name, this);
    return InvocationMockBuilderGetter(core, core);
}

//////////////////////////////////////////////////////////////
// Private
Invokable*
ChainableMockObject::getInvokable(const std::string& name) 
{
   return This->getMethod(name, this);
}

//////////////////////////////////////////////////////////////
void ChainableMockObject::reset()
{
   This->reset();
}

//////////////////////////////////////////////////////////////

MOCKCPP_NS_END


