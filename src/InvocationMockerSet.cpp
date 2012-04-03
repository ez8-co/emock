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

#include <list>
#include <algorithm>

#include <mockcpp/types/Any.h>
#include <mockcpp/InvocationMockerSet.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>


MOCKCPP_NS_START

namespace
{
   struct IsIdEqual
   {
      bool operator()(InvocationMocker* mocker) const
      {
         const InvocationId* const invId = mocker->getId();
         return invId && invId->getId() == id;
      }

      IsIdEqual(const std::string& identity)
         : id(identity)
      {}

      const std::string& id;
   };

   void deleteMocker(InvocationMocker* mocker)
   {
      delete mocker;
   }

   void verifyMocker(InvocationMocker* mocker)
   {
       mocker->verify();
   }

} // namespace

//////////////////////////////////////////////////////////////
InvocationMocker*
InvocationMockerSet::getInvocationMocker(const std::string& id) const
{
   ConstIterator i = find_if( mockers.begin()
                            , mockers.end()
                            , IsIdEqual(id));
   if(i == mockers.end())
   {
      return 0;
   }

   return (*i);
}

//////////////////////////////////////////////////////////////
void
InvocationMockerSet::reset()
{
    //for_each(mockers.begin(), mockers.end(), deleteMocker);
	for(Iterator i = mockers.begin(); i != mockers.end(); i++)
	{
		deleteMocker(*i);
	}

    mockers.clear();
	
	return;
}

//////////////////////////////////////////////////////////////
void
InvocationMockerSet::verify()
{
    for_each(mockers.begin(), mockers.end(), verifyMocker);
}

//////////////////////////////////////////////////////////////
void
InvocationMockerSet::addInvocationMocker(InvocationMocker* mocker)
{
    mockers.push_back(mocker);
}

//////////////////////////////////////////////////////////////
std::string
InvocationMockerSet::toString() const
{
    oss_t oss;
    ConstIterator i = mockers.begin();
    for(; i != mockers.end(); i++) {
       oss << (*i)->toString() << "\n\n"; 
    }

    return oss.str();
}

//////////////////////////////////////////////////////////////
const Any& 
InvocationMockerSet::invoke(const Invocation& inv
				, SelfDescribe* &resultProvider)
{
    for(Iterator i = mockers.begin(); i != mockers.end(); ++i) {
      if((*i)->matches(inv)) {
        resultProvider = *i;
        return (*i)->invoke(inv);
      }
    }

	return getEmptyAny();
}


MOCKCPP_NS_END

