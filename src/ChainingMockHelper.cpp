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

#include <mockcpp/mockcpp.h>

#include <mockcpp/Matcher.h>
#include <mockcpp/TypelessStubAdapter.h>
#include <mockcpp/InvokedOnce.h>
#include <mockcpp/InvokedAtLeast.h>
#include <mockcpp/InvokedAtMost.h>
#include <mockcpp/InvokedExactly.h>
#include <mockcpp/TestFailureMatcher.h>
#include <mockcpp/ReturnStub.h>
#include <mockcpp/ReturnObjectList.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/OutBoundPointer.h>
#include <mockcpp/IsMirror.h>
#include <mockcpp/IgnoreReturnStub.h>
#include <mockcpp/RepeatStub.h>
#include <mockcpp/StringConstraint.h>
#include <mockcpp/IsStringStartWith.h>
#include <mockcpp/IsStringEndWith.h>
#include <mockcpp/IsStringContains.h>
#include <mockcpp/DieStub.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT 
Matcher* once()
{
	return new InvokedOnce;
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Matcher* exactly(unsigned int times)
{
	return new InvokedExactly(times);
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Matcher* atLeast(unsigned int times)
{
	return new InvokedAtLeast(times);
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Matcher* atMost(unsigned int times)
{
	return new InvokedAtMost(times);
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Matcher* atLeastOnce()
{
	return atLeast(1);
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Matcher* atMostOnce()
{
	return atMost(1);
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Matcher* never()
{
   return new TestFailureMatcher(
				"Invoking an invocation which should never be invoked",
            "never()");
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Stub* returnValue(const Any& val)
{
   return new TypelessStubAdapter(new ReturnStub(val));
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Stub* repeat(const Any& val, unsigned int repeatTimes)
{
   return new TypelessStubAdapter(new RepeatStub(val, repeatTimes));
}

//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Stub* ignoreReturnValue()
{
   return new TypelessStubAdapter(new IgnoreReturnStub());
}

MOCKCPP_EXPORT
Stub* die(int code)
{
   return new TypelessStubAdapter(new DieStub(code));
}
//////////////////////////////////////////////////////////////////
MOCKCPP_EXPORT
Stub* returnObjectList( const Any& o01
                      , const Any& o02 
                      , const Any& o03
                      , const Any& o04
                      , const Any& o05
                      , const Any& o06
                      , const Any& o07
                      , const Any& o08
                      , const Any& o09
                      , const Any& o10
                      , const Any& o11
                      , const Any& o12)
{
    return new TypelessStubAdapter(
                 new ReturnObjectList(
                       o01, o02, o03, o04, o05, o06,
                       o07, o08, o09, o10, o11, o12));
}

MOCKCPP_EXPORT
Constraint* outBoundP(void* p, size_t size, Constraint* constraint)
{
   return new OutBoundPointer<void*>(p, size, constraint);
}

MOCKCPP_EXPORT
Constraint* mirror(void* p, size_t size)
{
   return new IsMirror<void*>(p, size);
}

MOCKCPP_EXPORT
Constraint* smirror(char* s)
{
   return new IsMirror<char*>(s, strlen(s)+1);
}

MOCKCPP_EXPORT
Constraint* smirror(const char* s)
{
   return new IsMirror<const char*>(s, strlen(s)+1);
}

MOCKCPP_EXPORT
Constraint* smirror(unsigned char* s)
{
   return new IsMirror<unsigned char*>(s, strlen((char*)s)+1);
}

MOCKCPP_EXPORT
Constraint* smirror(const unsigned char* s)
{
   return new IsMirror<const unsigned char*>(s, strlen((const char*)s)+1);
}

MOCKCPP_EXPORT
Constraint* startWith(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringStartWith());
}

MOCKCPP_EXPORT
Constraint* startWith(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringStartWith());
}

MOCKCPP_EXPORT
Constraint* startWith(const std::string& s)
{
    return new StringConstraint(s, new IsStringStartWith());
}

MOCKCPP_EXPORT
Constraint* endWith(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringEndWith());
}

MOCKCPP_EXPORT
Constraint* endWith(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringEndWith());
}

MOCKCPP_EXPORT
Constraint* endWith(const std::string& s)
{
    return new StringConstraint(s, new IsStringEndWith());
}

MOCKCPP_EXPORT
Constraint* contains(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringContains());
}

MOCKCPP_EXPORT
Constraint* contains(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringContains());
}

MOCKCPP_EXPORT
Constraint* contains(const std::string& s)
{
    return new StringConstraint(s, new IsStringContains());
}

MOCKCPP_NS_END
