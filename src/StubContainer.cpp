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

#include <mockcpp/StubContainer.h>
#include <mockcpp/Stub.h>
#include <mockcpp/OutputStringStream.h>
#include <list>

MOCKCPP_NS_START

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
    for(; iter != stubs.end(); iter++)
    {
       oss << "\n" << space << (*iter)->toString();
    }

    return oss.str();
}
//////////////////////////////////////////////
void StubContainerImpl::reset()
{
   for(Iterator i = stubs.begin(); \
                i != stubs.end(); i++)
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
       i++;
       iter++;
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
       iter++;
       index++;
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

MOCKCPP_NS_END

