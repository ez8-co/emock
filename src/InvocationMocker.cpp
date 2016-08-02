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

#include <mockcpp/InvocationMocker.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/Matcher.h>
#include <mockcpp/Stub.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/Method.h>
#include <mockcpp/StubContainer.h>

#include <list>
#include <algorithm>

MOCKCPP_NS_START

namespace
{
   const std::string normalSpace = "     ";

   const std::string& space()
   {
	    return normalSpace;
   }
}
///////////////////////////////////////////////////////////
struct InvocationMockerImpl
{
public:
    typedef std::list<Matcher*>  List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

	///////////////////////////////////////////////////
    List matchers;
    Method* belongedMethod;
    bool hasBeenInvoked;
    InvocationId* id ;

    StubContainer stubs;
	///////////////////////////////////////////////////
    InvocationMockerImpl(Method* method)
		: belongedMethod(method), hasBeenInvoked(false), id(0), stubs(space())
    {}

    ~InvocationMockerImpl()
    { reset(); }

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);
    Any& invoke(const Invocation& inv);

    void reset();
    void verify();
    std::string toString() const;
};

/////////////////////////////////////////////////////////


std::string
InvocationMockerImpl::toString() const
{
    std::ostringstream ss;

    ss << "method(" << belongedMethod->getName() << ")";

    for (ConstIterator i = matchers.begin(); i != matchers.end(); ++i)
    {
      ss << "\n" << space() << (*i)->toString();
    }

    ss << stubs.toString();

    if(id != 0)
    {
      ss << "\n" << space() << id->toString();
    }
   
    ss << ";";

    return ss.str();
}

/////////////////////////////////////////////////////////
namespace
{
    void verifyMatcher(Matcher* matcher)
    {
      matcher->verify();
    }
}

/////////////////////////////////////////////////////////
void InvocationMockerImpl::verify()
{
    for_each(matchers.begin(), matchers.end(), verifyMatcher);
}

/////////////////////////////////////////////////////////
namespace
{
    void deleteMatcher(Matcher* matcher)
    {
      delete matcher;
    }
}

///////////////////////////////////////////////////////////
void InvocationMockerImpl::reset()
{
    for_each(matchers.begin(), matchers.end(), deleteMatcher);

    matchers.clear();

    stubs.reset();

    if (id != 0)
    {
      delete id;
      id = 0;
    }
}

///////////////////////////////////////////////////////////
bool
InvocationMockerImpl::matches(const Invocation& inv) const
{
    ConstIterator i = matchers.begin();
    for (; i != matchers.end(); ++i)
    {
      if (!(*i)->matches(inv))
      {
        return false;
      }
    }

    return true;
}

///////////////////////////////////////////////////////////
void
InvocationMockerImpl::increaseInvoked(const Invocation& inv) 
{
    for (Iterator i = matchers.begin(); i != matchers.end(); ++i)
    {
      (*i)->increaseInvoked(inv);
    }
}

///////////////////////////////////////////////////////////
Any&
InvocationMockerImpl::invoke(const Invocation& inv)
{
    increaseInvoked(inv);

    hasBeenInvoked = true;

    Stub* stub = stubs.getStub();
    if (stub != 0)
    {
      return stub->invoke(inv);
    } 

    return getVoidAny();
}

///////////////////////////////////////////////////////////
InvocationMocker::InvocationMocker(Method* method)
   : This(new InvocationMockerImpl(method))
{
}

///////////////////////////////////////////////////////////
InvocationMocker::~InvocationMocker()
{
    delete This;
}

///////////////////////////////////////////////////////////
Method*
InvocationMocker::getMethod() const
{
    return This->belongedMethod;
}

///////////////////////////////////////////////////////////
void InvocationMocker::setId(InvocationId* id)
{
    if (This->id != 0) delete This->id;

    This->id = id;
}

///////////////////////////////////////////////////////////
void InvocationMocker::addMatcher(Matcher* matcher)
{
    This->matchers.push_back(matcher);
}

///////////////////////////////////////////////////////////
bool InvocationMocker::hasBeenInvoked(void) const
{
    return This->hasBeenInvoked;
}

///////////////////////////////////////////////////////////
void InvocationMocker::addStub(Stub* stub) 
{
    This->stubs.addStub(stub);
}

///////////////////////////////////////////////////////////
const InvocationId* const InvocationMocker::getId(void) const
{
    return This->id;
}

///////////////////////////////////////////////////////////
bool InvocationMocker::matches(const Invocation& inv) const
{
    return This->matches(inv);
}

///////////////////////////////////////////////////////////
std::string InvocationMocker::toString() const
{
    return This->toString();
}

///////////////////////////////////////////////////////////
Any& InvocationMocker::invoke(const Invocation& inv)
{
    try
    {
      return This->invoke(inv);
    }
    catch (Exception& ex)
    {
      MOCKCPP_FAIL(ex.getMessage() + "\n" + This->toString());
    }

	return getEmptyAny();
}

///////////////////////////////////////////////////////////
void InvocationMocker::verify()
{
    try
    {
      This->verify();
    }
    catch (Exception& ex)
    {
      MOCKCPP_FAIL(ex.getMessage() + "\n" + This->toString());
    }
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

