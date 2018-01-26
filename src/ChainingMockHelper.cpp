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

#include <emock/emock.h>

#include <emock/Matcher.h>
#include <emock/TypelessStubAdapter.h>
#include <emock/InvokedOnce.h>
#include <emock/InvokedAtLeast.h>
#include <emock/InvokedAtMost.h>
#include <emock/InvokedExactly.h>
#include <emock/TestFailureMatcher.h>
#include <emock/ReturnStub.h>
#include <emock/ReturnObjectList.h>
#include <emock/Constraint.h>
#include <emock/OutBoundPointer.h>
#include <emock/IsMirror.h>
#include <emock/IgnoreReturnStub.h>
#include <emock/RepeatStub.h>
#include <emock/StringConstraint.h>
#include <emock/IsStringStartWith.h>
#include <emock/IsStringEndWith.h>
#include <emock/IsStringContains.h>
#include <emock/DieStub.h>

EMOCK_NS_START

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT 
Matcher* once()
{
	return new InvokedOnce;
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Matcher* exactly(unsigned int times)
{
	return new InvokedExactly(times);
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Matcher* atLeast(unsigned int times)
{
	return new InvokedAtLeast(times);
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Matcher* atMost(unsigned int times)
{
	return new InvokedAtMost(times);
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Matcher* atLeastOnce()
{
	return atLeast(1);
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Matcher* atMostOnce()
{
	return atMost(1);
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Matcher* never()
{
   return new TestFailureMatcher(
				"Invoking an invocation which should never be invoked",
            "never()");
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Stub* returnValue(const Any& val)
{
   return new TypelessStubAdapter(new ReturnStub(val));
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Stub* repeat(const Any& val, unsigned int repeatTimes)
{
   return new TypelessStubAdapter(new RepeatStub(val, repeatTimes));
}

//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
Stub* ignoreReturnValue()
{
   return new TypelessStubAdapter(new IgnoreReturnStub());
}

EMOCK_EXPORT
Stub* die(int code)
{
   return new TypelessStubAdapter(new DieStub(code));
}
//////////////////////////////////////////////////////////////////
EMOCK_EXPORT
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

EMOCK_EXPORT
Constraint* outBoundP(void* p, size_t size, Constraint* constraint)
{
   return new OutBoundPointer<void*>(p, size, constraint);
}

EMOCK_EXPORT
Constraint* mirror(void* p, size_t size)
{
   return new IsMirror<void*>(p, size);
}

EMOCK_EXPORT
Constraint* smirror(char* s)
{
   return new IsMirror<char*>(s, strlen(s)+1);
}

EMOCK_EXPORT
Constraint* smirror(const char* s)
{
   return new IsMirror<const char*>(s, strlen(s)+1);
}

EMOCK_EXPORT
Constraint* smirror(unsigned char* s)
{
   return new IsMirror<unsigned char*>(s, strlen((char*)s)+1);
}

EMOCK_EXPORT
Constraint* smirror(const unsigned char* s)
{
   return new IsMirror<const unsigned char*>(s, strlen((const char*)s)+1);
}

EMOCK_EXPORT
Constraint* startWith(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringStartWith());
}

EMOCK_EXPORT
Constraint* startWith(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringStartWith());
}

EMOCK_EXPORT
Constraint* startWith(const std::string& s)
{
    return new StringConstraint(s, new IsStringStartWith());
}

EMOCK_EXPORT
Constraint* endWith(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringEndWith());
}

EMOCK_EXPORT
Constraint* endWith(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringEndWith());
}

EMOCK_EXPORT
Constraint* endWith(const std::string& s)
{
    return new StringConstraint(s, new IsStringEndWith());
}

EMOCK_EXPORT
Constraint* contains(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringContains());
}

EMOCK_EXPORT
Constraint* contains(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringContains());
}

EMOCK_EXPORT
Constraint* contains(const std::string& s)
{
    return new StringConstraint(s, new IsStringContains());
}

EMOCK_NS_END
