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

