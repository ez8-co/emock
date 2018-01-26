/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.

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

#include <emock/StubContainer.h>
#include <emock/Stub.h>
#include <emock/OutputStringStream.h>
#include <list>

EMOCK_NS_START

//////////////////////////////////////////////
struct StubContainerImpl
{
   typedef std::list<Stub*> List;
   typedef List::const_iterator ConstIterator;
   typedef List::iterator Iterator;

   List stubs;
   mutable unsigned int index;

   StubContainerImpl(const std::string&);
   ~StubContainerImpl();

   void addStub(Stub* stub);

   void reset();

   bool isLast() const;

   Stub* getStub() const;

   ConstIterator getCurrentStub() const;
  
   std::string toString() const;
   
   const std::string space;
};

//////////////////////////////////////////////
StubContainerImpl::StubContainerImpl(const std::string& s)
    : space(s)
{
   index = 0;
}

std::string StubContainerImpl::toString() const
{
    oss_t oss;

    ConstIterator iter = stubs.begin();
    for(; iter != stubs.end(); ++iter)
    {
       oss << "\n" << space << (*iter)->toString();
    }

    return oss.str();
}
//////////////////////////////////////////////
void StubContainerImpl::reset()
{
   for(Iterator i = stubs.begin(); \
                i != stubs.end(); ++i)
   {
      delete (*i);
   }
   
   stubs.clear();
}

//////////////////////////////////////////////
StubContainerImpl::~StubContainerImpl()
{
   reset();
}

//////////////////////////////////////////////
bool StubContainerImpl::isLast() const
{
   return (index + 1) >= stubs.size();
}

//////////////////////////////////////////////
void StubContainerImpl::addStub(Stub* stub) 
{
    stubs.push_back(stub);
}

//////////////////////////////////////////////
StubContainerImpl::ConstIterator StubContainerImpl::getCurrentStub() const
{
    ConstIterator iter = stubs.begin();
    unsigned int i = 0;
    while(i < index && iter != stubs.end())
    {
       ++i;
       ++iter;
    }

    return iter;
}
//////////////////////////////////////////////
Stub* StubContainerImpl::getStub() const
{
    ConstIterator iter = getCurrentStub();
    if(iter == stubs.end())
    {
       return 0;
    }

    if((*iter)->isCompleted() && !isLast())
    {
       ++iter;
       ++index;
    }

    return (*iter);
}

////////////////////////////////////////////
StubContainer::StubContainer(const std::string& s)
   : This(new StubContainerImpl(s))
{
}

////////////////////////////////////////////
StubContainer::~StubContainer()
{
   delete This;
}

////////////////////////////////////////////
void StubContainer::addStub(Stub* stub)
{
   This->addStub(stub);
}

////////////////////////////////////////////
Stub* StubContainer::getStub() const
{
   return This->getStub();
}

////////////////////////////////////////////
void StubContainer::reset()
{
   return This->reset();
}
////////////////////////////////////////////
std::string StubContainer::toString() const
{
   return This->toString();
}

EMOCK_NS_END

