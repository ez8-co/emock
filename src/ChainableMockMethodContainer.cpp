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

#include <mockcpp/ChainableMockMethodContainer.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/ChainableMockMethodKey.h>
#include <mockcpp/ReportFailure.h>

#include <list>
#include <utility>
#include <algorithm>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////////////
struct ChainableMockMethodContainerImpl
{
   typedef std::pair<ChainableMockMethodKey*, \
                     ChainableMockMethodCore*> ValueType;
   typedef std::list<ValueType> List;
   typedef List::iterator Iterator;
   typedef List::const_iterator ConstIterator;

   ChainableMockMethodContainerImpl()
      : verified(false) {}

   ~ChainableMockMethodContainerImpl();

   ChainableMockMethodCore*
   getMethod(ChainableMockMethodKey* key) const;

   void addMethod(ChainableMockMethodKey* key, \
              ChainableMockMethodCore* method);

   InvocationMocker* findInvocationMocker(const std::string& id) const;

   void reset();
   void verify();

   bool verified;
   List methods;
};

/////////////////////////////////////////////////////////////////////////
namespace
{
  inline ChainableMockMethodKey* getKey(ChainableMockMethodContainerImpl::ValueType& value)
  {
    return value.first;
  }

  inline ChainableMockMethodCore* getMethodCore(ChainableMockMethodContainerImpl::ValueType& value)
  {
    return value.second;
  }

  void resetMethod(ChainableMockMethodContainerImpl::ValueType value)
  {
    getMethodCore(value)->reset();

    // We don't know wether MethodCore is referring a "key" or not,
	// so if we delete the key prior to methodCore might result in
	// unexpected behavior.
    delete getMethodCore(value);

    delete getKey(value);
  }
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainerImpl::reset()
{
    //for_each(methods.begin(), methods.end(), resetMethod);
	for(Iterator i = methods.begin(); i != methods.end(); i++)
	{
		resetMethod(*i);
	}
    methods.clear();
    verified = false;
}

/////////////////////////////////////////////////////////////////////////
namespace
{
  void verifyMethod(ChainableMockMethodContainerImpl::ValueType value)
  {
    value.second->verify();
  }
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainerImpl::verify()
{
    if(verified) return;

    verified = true;

    for_each(methods.begin(), methods.end(), verifyMethod);
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodContainerImpl::~ChainableMockMethodContainerImpl()
{
   reset();
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainerImpl::addMethod(ChainableMockMethodKey* key, \
              ChainableMockMethodCore* method)
{
    methods.push_back(ValueType(key, method));
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodContainer::ChainableMockMethodContainer()
   : This(new ChainableMockMethodContainerImpl())
{
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodContainer::~ChainableMockMethodContainer()
{
   delete This;
}

/////////////////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodContainerImpl::findInvocationMocker(const std::string& id) const
{
   for (ConstIterator i = methods.begin(); i != methods.end(); ++i)
   {
	  InvocationMocker* mocker = i->second->getInvocationMocker(id);
      if(mocker != 0)
      {
         return mocker;
      }
   }

   return 0;
}

/////////////////////////////////////////////////////////////////////////
namespace
{
  struct IsMethodKeyMatch
  {
    IsMethodKeyMatch(ChainableMockMethodKey* key)
      : myKey(key)
    {}

    bool operator()(ChainableMockMethodContainerImpl::ValueType value)
    {
       return myKey->equals(getKey(value));
    }

    ChainableMockMethodKey* myKey;
  };

}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockMethodContainerImpl::getMethod(ChainableMockMethodKey* key) const
{
    ConstIterator i = std::find_if( methods.begin()
                                  , methods.end()
                                  , IsMethodKeyMatch(key));

    return (i == methods.end()) ? 0 : i->second;
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockMethodContainer::getMethod(ChainableMockMethodKey* key) const
{
    return This->getMethod(key);
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainer::addMethod(ChainableMockMethodKey* key, \
              ChainableMockMethodCore* method)
{
    if(getMethod(key) != 0)
    {
       MOCKCPP_REPORT_FAILURE("internal error (1022), please report this bug to" PACKAGE_BUGREPORT ".");
    }

    This->addMethod(key, method);
}

/////////////////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodContainer::findInvocationMocker(const std::string& id) const
{
    return This->findInvocationMocker(id);
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainer::reset()
{
   This->reset();
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainer::verify()
{
   This->verify();
}

/////////////////////////////////////////////////////////////////////////
MOCKCPP_NS_END

