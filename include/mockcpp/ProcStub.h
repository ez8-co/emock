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

#ifndef __MOCKCPP_PROC_STUB_H
#define __MOCKCPP_PROC_STUB_H

#include <mockcpp/types/RefAny.h>
#include <mockcpp/types/AnyCast.h>

#include <mockcpp/Stub.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

MOCKCPP_NS_START

template <typename F>
struct ProcStub;

struct ProcStubBaseImpl;

struct ProcStubBase : public Stub
{
    ProcStubBase(const std::string& name, void* addr);

    ~ProcStubBase();

    bool isCompleted() const;

    std::string toString() const;
    
private:

    ProcStubBaseImpl* This;
};

////////////////////////////////////////////////////
std::string getParameterMismatchString(int n
                , std::string p
                , const Invocation& inv);

////////////////////////////////////////////////////
#define MOCKCPP_CHECK_AND_ASSIGN_PARAMETER(N) \
        MOCKCPP_ASSERT_TRUE_MESSAGE( \
                    getParameterMismatchString(N, TypeString<MOCKP##N>::value(), inv) \
                        , any_castable<MOCKP##N>(inv.getParameter(N))); \
        MOCKP##N p##N = any_cast<MOCKP##N>(inv.getParameter(N));
    
#define PROC_STUB_CONS()  \
    ProcStub(Func f, std::string name) \
        : ProcStubBase(name, (void*)f), func(f) \
    {} 


///////////////////////////////////////////////////////////
#define __PROC_STUB_DEF(n, CallingConvention) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct ProcStub<R CallingConvention (DECL_ARGS(n))> : public ProcStubBase \
{ \
    typedef R (CallingConvention *Func)(DECL_ARGS(n)); \
 \
    PROC_STUB_CONS() \
 \
    Any& invoke(const Invocation& inv) \
    { \
        SIMPLE_REPEAT(n, MOCKCPP_CHECK_AND_ASSIGN_PARAMETER); \
 \
        result = func(DECL_PARAMS(n)); \
        return result; \
    } \
 \
private: \
    Func func; \
    Any result; \
}; \
template <typename R DECL_TEMPLATE_ARGS(n)> \
Stub* invoke(R(CallingConvention *f)(DECL_ARGS(n)), const char* name = 0) \
{ \
    return new ProcStub<R CallingConvention (DECL_ARGS(n))>(f, name?name:""); \
} \
template <DECL_VOID_TEMPLATE_ARGS(n)> \
struct ProcStub<void CallingConvention (DECL_ARGS(n))> : public ProcStubBase \
{ \
    typedef void (CallingConvention *Func)(DECL_ARGS(n)); \
 \
    PROC_STUB_CONS() \
 \
    Any& invoke(const Invocation& inv) \
    { \
        SIMPLE_REPEAT(n, MOCKCPP_CHECK_AND_ASSIGN_PARAMETER); \
 \
        func(DECL_PARAMS(n)); \
        return getVoidAny(); \
    } \
 \
private: \
    Func func; \
}

#if defined(_MSC_VER)
#define PROC_STUB_DEF(n) \
__PROC_STUB_DEF(n, ); \
__PROC_STUB_DEF(n, __stdcall)
#else
#define PROC_STUB_DEF(n) \
__PROC_STUB_DEF(n, )
#endif
/////////////////////////////////////////////////////

PROC_STUB_DEF(0);
PROC_STUB_DEF(1);
PROC_STUB_DEF(2);
PROC_STUB_DEF(3);
PROC_STUB_DEF(4);
PROC_STUB_DEF(5);
PROC_STUB_DEF(6);
PROC_STUB_DEF(7);
PROC_STUB_DEF(8);
PROC_STUB_DEF(9);
PROC_STUB_DEF(10);
PROC_STUB_DEF(11);
PROC_STUB_DEF(12);

#define VARDIC_PROC_STUB_DEF(n)  \
template <typename R DECL_TEMPLATE_ARGS(n)>  \
struct ProcStub<R (DECL_VARDIC_ARGS(n) ...)> : public ProcStubBase \
{ \
    typedef R (*Func)(DECL_VARDIC_ARGS(n) ...); \
 \
    PROC_STUB_CONS() \
 \
    Any& invoke(const Invocation& inv) \
    { \
        SIMPLE_REPEAT(n, MOCKCPP_CHECK_AND_ASSIGN_PARAMETER); \
 \
        result = func(DECL_PARAMS(n)); \
        return result; \
    } \
 \
private: \
    Func func; \
    Any result; \
}; \
template <typename R DECL_TEMPLATE_ARGS(n)> \
Stub* invoke(R(*f)(DECL_VARDIC_ARGS(n) ...), const char* name = 0) \
{ \
    return new ProcStub<R (DECL_VARDIC_ARGS(n) ...)>(f, name?name:""); \
} \
template <DECL_VOID_TEMPLATE_ARGS(n)> \
struct ProcStub<void (DECL_VARDIC_ARGS(n) ...)> : public ProcStubBase \
{ \
    typedef void (*Func)(DECL_VARDIC_ARGS(n) ...); \
 \
    PROC_STUB_CONS() \
 \
    Any& invoke(const Invocation& inv) \
    { \
        SIMPLE_REPEAT(n, MOCKCPP_CHECK_AND_ASSIGN_PARAMETER); \
 \
        func(DECL_PARAMS(n)); \
        return getVoidAny(); \
    } \
 \
private: \
    Func func; \
}

/////////////////////////////////////////////////////
VARDIC_PROC_STUB_DEF(0);
VARDIC_PROC_STUB_DEF(1);
VARDIC_PROC_STUB_DEF(2);
VARDIC_PROC_STUB_DEF(3);
VARDIC_PROC_STUB_DEF(4);
VARDIC_PROC_STUB_DEF(5);
VARDIC_PROC_STUB_DEF(6);
VARDIC_PROC_STUB_DEF(7);
VARDIC_PROC_STUB_DEF(8);

/////////////////////////////////////////////////////

#define PROC(function) function, #function

/////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

