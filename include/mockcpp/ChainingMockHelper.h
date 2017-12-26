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

#ifndef __MOCKCPP_CHAINING_MOCK_HELPER_H
#define __MOCKCPP_CHAINING_MOCK_HELPER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/IsEqual.h>
#include <mockcpp/IsNotEqual.h>
#include <mockcpp/IsGreaterThan.h>
#include <mockcpp/IsLessThan.h>
#include <mockcpp/IsMirror.h>
#include <mockcpp/Spy.h>
#include <mockcpp/CheckWith.h>
#include <mockcpp/ProcessWith.h>
#include <mockcpp/OutBound.h>
#include <mockcpp/OutBoundPointer.h>
#include <mockcpp/IncrementStub.h>
#include <mockcpp/ThrowExceptionStub.h>
#include <mockcpp/TypelessStubAdapter.h>
#include <mockcpp/types/Any.h>
#include <mockcpp/ProcStub.h>

MOCKCPP_NS_START

struct Matcher;
struct Stub;

Matcher* once();
Matcher* never();
Matcher* atLeast(unsigned int times);
Matcher* atMost(unsigned int times);
Matcher* exactly(unsigned int times);

template <typename T>
Constraint* eq(const T& val)
{
	return new IsEqual<T>(val);
}

template <typename T>
Constraint* neq(const T& val)
{
	return new IsNotEqual<T>(val);
}

template <typename T>
Constraint* gt(const T& val)
{
   return new IsGreaterThan<T>(val);
}

template <typename T>
Constraint* lt(const T& val)
{
   return new IsLessThan<T>(val);
}

////////////////////////////////////////////////////////////////
#if 0
static inline Constraint* eq(const char* s)
{
   return new IsEqual<const char*>(s);
}
#endif

template <typename T>
Constraint* spy(T& val)
{
   return new Spy<T>(val);
}

template <typename Predict, typename T>
Constraint* checkWithHelper(bool (Predict::*)(T), Predict pred)
{
    return new CheckWith<T, Predict>(pred);
}

template <typename Predict>
Constraint* checkWith(Predict pred)
{
    return checkWithHelper(&Predict::operator(), pred);
}

////////////////////////////////////////////////////////////////
template <typename T>
Constraint* checkWith(bool (*pred)(T))
{
    return new CheckWith<T, bool (*)(T)>(pred);
}

////////////////////////////////////////////////////////////////

template <typename Predict, typename T>
Constraint* processWithHelper(bool (Predict::*)(T), Predict pred)
{
    return new ProcessWith<T, Predict>(pred);
}

template <typename Proc>
Constraint* processWith(Proc proc)
{
    return processWithHelper(&Proc::operator(), proc);
}

////////////////////////////////////////////////////////////////
template <typename T>
Constraint* processWith(void (*proc)(T))
{
    return new ProcessWith<T, void (*)(T)>(proc);
}

////////////////////////////////////////////////////////////////
template <typename T>
Constraint* outBound(const T& val, Constraint* constraint = 0)
{
   return new OutBound<T>(val, constraint);
}

////////////////////////////////////////////////////////////////
// outBoundP
////////////////////////////////////////////////////////////////
template <typename T>
Constraint* outBoundP(T* p, size_t size, Constraint* constraint = 0)
{
   return new OutBoundPointer<T*>(p, size, constraint);
}

////////////////////////////////////////////////////////////////
Constraint* outBoundP(void* p, size_t size, Constraint* constraint = 0);

////////////////////////////////////////////////////////////////
template <typename T>
Constraint* outBoundP(T* p, Constraint* constraint = 0)
{
   return new OutBoundPointer<T*>(p, sizeof(T), constraint);
}

///////////////////////////////////////////////////////////////////
// mirror
///////////////////////////////////////////////////////////////////
#if defined(__GNUC__) && (__GNUC__ > 3)
template <typename T>
Constraint* mirror(const T& obj)
{
   return new IsMirror<T>(obj);
}
#endif

///////////////////////////////////////////////////////////////////
template <typename T>
Constraint* mirror(T* p, size_t size = 0)
{
   return new IsMirror<T*>(p, size);
}

///////////////////////////////////////////////////////////////////
Constraint* mirror(void* p, size_t size);

#if 0
Constraint* startWith(char*);
Constraint* startWith(const char*);
Constraint* startWith(unsigned char*);
Constraint* startWith(unsigned const char*);
#endif
Constraint* startWith(const std::string&);

#if 0
Constraint* endWith(char*);
Constraint* endWith(const char*);
Constraint* endWith(unsigned char*);
Constraint* endWith(unsigned const char*);
#endif

Constraint* endWith(const std::string&);

#if 0
Constraint* contains(char*);
Constraint* contains(const char*);
Constraint* contains(unsigned char*);
Constraint* contains(unsigned const char*);
#endif

Constraint* contains(const std::string&);
///////////////////////////////////////////////////////////////////
// smirror
///////////////////////////////////////////////////////////////////
Constraint* smirror(char* s);
Constraint* smirror(const char* s);
Constraint* smirror(unsigned char* s);
Constraint* smirror(const unsigned char* s);
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
Stub* die(int code = 0);

Stub* returnValue(const Any& val);

Stub* repeat(const Any& val, unsigned int repeatTimes);

Stub* ignoreReturnValue();

Stub* returnObjectList( const Any& o01
                      , const Any& o02 = Any()
                      , const Any& o03 = Any()
                      , const Any& o04 = Any()
                      , const Any& o05 = Any()
                      , const Any& o06 = Any()
                      , const Any& o07 = Any()
                      , const Any& o08 = Any()
                      , const Any& o09 = Any()
                      , const Any& o10 = Any()
                      , const Any& o11 = Any()
                      , const Any& o12 = Any());


template <typename T>
Stub* increase(const T& from, const T& to)
{
   return new TypelessStubAdapter(new IncrementStub<T>(from, to));
}

template <typename T>
Stub* increase(const T& from)
{
   return new TypelessStubAdapter(new IncrementStub<T>(from));
}

template <typename T>
Stub* throws(const T& ex)
{
   return new TypelessStubAdapter(new ThrowExceptionStub<T>(ex));
}

MOCKCPP_NS_END

#endif

