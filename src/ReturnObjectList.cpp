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

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/ReturnObjectList.h>
#include <mockcpp/Asserter.h>

#include <vector>

MOCKCPP_NS_START

struct ReturnObjectListImpl
{
    typedef std::vector<Any> Objects;

    unsigned int firstUnused;

    Objects objects;

    ReturnObjectListImpl() : firstUnused(0) {}

    bool isCompleted() const;

    unsigned int numberOfValidObjects() const;

    Any& invoke();

    std::string toString() const;

	const std::type_info& type() const;
};

///////////////////////////////////////////////////////
const std::type_info& ReturnObjectListImpl::type() const
{
    if (firstUnused >= objects.size()) return getEmptyAny().type();

    return objects[firstUnused].type();
}

///////////////////////////////////////////////////////
std::string ReturnObjectListImpl::toString() const
{
    oss_t oss;

    unsigned int n = numberOfValidObjects();
    for (unsigned int i = 0; i < n; i++)
    {
      if (i > 0) oss << ",";
      oss << objects[i].toTypeAndValueString();
    }

    return oss.str();
}

///////////////////////////////////////////////////////
unsigned int ReturnObjectListImpl::numberOfValidObjects() const
{
    for (size_t i = objects.size()-1; i >= 0; i--)
    {
      if(!objects[i].empty()) return (unsigned int)(i+1);
    }

    return 0;
}

///////////////////////////////////////////////////////
bool ReturnObjectListImpl::isCompleted() const
{
    return firstUnused < numberOfValidObjects();
}
///////////////////////////////////////////////////////
Any& ReturnObjectListImpl::invoke()
{
    if(firstUnused < numberOfValidObjects())
    {
      return objects[firstUnused++];
    }
    
    MOCKCPP_FAIL("All objects has been returned");

    return getEmptyAny();
}

///////////////////////////////////////////////////////
#define STORE_OBJECTS(i) This->objects.push_back(o##i)

ReturnObjectList::ReturnObjectList(
                      const Any& o1 
                    , const Any& o2 
                    , const Any& o3
                    , const Any& o4 
                    , const Any& o5
                    , const Any& o6 
                    , const Any& o7
                    , const Any& o8
                    , const Any& o9 
                    , const Any& o10 
                    , const Any& o11 
                    , const Any& o12 
    ) : This(new ReturnObjectListImpl)
{
    STORE_OBJECTS(1);
    STORE_OBJECTS(2);
    STORE_OBJECTS(3);
    STORE_OBJECTS(4);
    STORE_OBJECTS(5);
    STORE_OBJECTS(6);
    STORE_OBJECTS(7);
    STORE_OBJECTS(8);
    STORE_OBJECTS(9);
    STORE_OBJECTS(10);
    STORE_OBJECTS(11);
    STORE_OBJECTS(12);
}

///////////////////////////////////////////////////
ReturnObjectList::~ReturnObjectList()
{
    delete This;
}

///////////////////////////////////////////////////
Any& ReturnObjectList::invoke(void)
{
    return This->invoke();
}

///////////////////////////////////////////////////
std::string ReturnObjectList::toString(void) const
{
    oss_t oss;

    oss << "returnObjectList(" << This->toString() << ")";

    return oss.str();
}

///////////////////////////////////////////////////
const std::type_info& ReturnObjectList::type() const
{
    return This->type();   
}

///////////////////////////////////////////////////
bool ReturnObjectList::isCompleted() const
{
    return This->isCompleted();
}
///////////////////////////////////////////////////

MOCKCPP_NS_END

