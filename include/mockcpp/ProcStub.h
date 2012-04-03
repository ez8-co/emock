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
#define PROC_STUB_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct ProcStub<R(DECL_ARGS(n))> : public ProcStubBase \
{ \
    typedef R (*Func)(DECL_ARGS(n)); \
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
Stub* invoke(R(*f)(DECL_ARGS(n)), const char* name = 0) \
{ \
    return new ProcStub<R(DECL_ARGS(n))>(f, name?name:""); \
} \
template <DECL_VOID_TEMPLATE_ARGS(n)> \
struct ProcStub<void(DECL_ARGS(n))> : public ProcStubBase \
{ \
    typedef void (*Func)(DECL_ARGS(n)); \
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

#define VARDIC_PROC_STUB_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)>  \
struct ProcStub<R(DECL_VARDIC_ARGS(n) ...)> : public ProcStubBase \
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
    return new ProcStub<R(DECL_VARDIC_ARGS(n) ...)>(f, name?name:""); \
} \
template <DECL_VOID_TEMPLATE_ARGS(n)> \
struct ProcStub<void(DECL_VARDIC_ARGS(n) ...)> : public ProcStubBase \
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

