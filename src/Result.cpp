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

#include <mockcpp/types/Any.h>

#include <mockcpp/Result.h>
#include <mockcpp/SelfDescribe.h>
#include <mockcpp/ResultHandler.h>

#include <mockcpp/IgnoreResultHandlerFactory.h>
#include <mockcpp/VoidResultHandlerFactory.h>
#include <mockcpp/MismatchResultHandlerFactory.h>
#include <mockcpp/NormalResultHandlerFactory.h>
#include <mockcpp/SelfDescribe.h>

#include <typeinfo>
#include <list>

MOCKCPP_NS_START

namespace {

IgnoreResultHandlerFactory ignoreResultHandlerFactory;
VoidResultHandlerFactory voidResultHandlerFactory;
NormalResultHandlerFactory normalResultHandlerFactory;
MismatchResultHandlerFactory mismatchResultHandlerFactory;

ResultHandlerFactory* const resultHandlerFactorys[] =
{
   &ignoreResultHandlerFactory,
   &voidResultHandlerFactory,
   &normalResultHandlerFactory,
   &mismatchResultHandlerFactory
};

const unsigned int numberOfResultHandlerFactorys = 4;
	//sizeof(resultHandlerFactorys)/sizeof(resultHandlerFactorys[0]);
}

struct ResultImpl
{
    std::list<ResultHandler*> handlers;

    const Any& getResult(const Any& result) const;

    ResultImpl( bool isCastable
          , const std::type_info& typeInfo
          , const std::string& typeString
          , const SelfDescribe* selfDescriber);

    ~ResultImpl();
};

/////////////////////////////////////////////////////////
ResultImpl::ResultImpl(
      bool isCastable
    , const std::type_info& typeInfo
	 , const std::string& typeString
	 , const SelfDescribe* selfDescriber)
{
   for(unsigned int i=0; i < numberOfResultHandlerFactorys; i++)
   {
      handlers.push_back(
                  resultHandlerFactorys[i]->create( isCastable
                                                  , typeInfo
                                                  , typeString
                                                  , selfDescriber));
   }
}

/////////////////////////////////////////////////////////
ResultImpl::~ResultImpl()
{
   std::list<ResultHandler*>::iterator i = handlers.begin();
   for(; i != handlers.end(); i++)
   {
      delete (*i);
   }

   handlers.clear();
}
//////////////////////////////////////////////////////////
Result::Result(
            bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
   : This(new ResultImpl( isCastable
                        , expectedTypeInfo
                        , expectedTypeString
                        , selfDescriber))
{
}

//////////////////////////////////////////////////////////
Result::~Result()
{
    delete This;
}

//////////////////////////////////////////////////////////
const Any& ResultImpl::getResult(const Any& result) const
{
    std::list<ResultHandler*>::const_iterator i = handlers.begin();
    for(; i != handlers.end(); i++)
    {
      if((*i)->matches(result))
      {
        return (*i)->getResult(result);
      }
    }

    return getEmptyAny();
}

//////////////////////////////////////////////////////////
const Any& Result::getResult(const Any& result) const
{
    return This->getResult(result);
}

MOCKCPP_NS_END

