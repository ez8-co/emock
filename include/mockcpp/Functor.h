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

#ifndef __MOCKCPP_FUNCTOR_H
#define __MOCKCPP_FUNCTOR_H

#include <mockcpp/mockcpp.h>

#include <string>

#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

#ifdef MOCKCPP_USE_MOCKABLE

MOCKCPP_NS_START

template<typename F, typename T>
T MockableConv(F func);

#ifdef _MSC_VER

  #define MOCKABLE_CONV_DEF(n)\
  template <typename R, typename CLS DECL_TEMPLATE_ARGS(n)>\
  R ( *MockableConv(R (CLS::*api)(DECL_ARGS(n))) )(DECL_ARGS(n))\
  {\
      union {\
        R (__stdcall *pf)(DECL_ARGS(n));\
        R (CLS::*pmf)(DECL_ARGS(n));\
      } u;\
      u.pmf = api;\
      return u.pf;\
  }

#else

  #define MOCKABLE_CONV_DEF(n)\
  template <typename R, typename CLS DECL_TEMPLATE_ARGS(n)>\
  R ( *MockableConv(R (CLS::*api)(DECL_ARGS(n))) )(CLS* DECL_REST_ARGS(n))\
  {\
      union {\
        R (*pf)(CLS* DECL_REST_ARGS(n));\
        R (CLS::*pmf)(DECL_ARGS(n));\
      } u;\
      u.pmf = api;\
      return u.pf;\
  }

#endif

MOCKABLE_CONV_DEF(0)
MOCKABLE_CONV_DEF(1)
MOCKABLE_CONV_DEF(2)
MOCKABLE_CONV_DEF(3)
MOCKABLE_CONV_DEF(4)
MOCKABLE_CONV_DEF(5)
MOCKABLE_CONV_DEF(6)
MOCKABLE_CONV_DEF(7)
MOCKABLE_CONV_DEF(8)
MOCKABLE_CONV_DEF(9)
MOCKABLE_CONV_DEF(10)
MOCKABLE_CONV_DEF(11)
MOCKABLE_CONV_DEF(12)

template<typename T>
PlaceHolder* MockableHelper(T func);

template<typename T>
struct RetValueImpl;

#define MOCKABLE_HELPER_DEF(n) \
  template<typename R DECL_TEMPLATE_ARGS(n)> \
  PlaceHolder* MockableHelper(R (*)(DECL_ARGS(n))) {\
    return new RetValueImpl<R>();\
  }

MOCKABLE_HELPER_DEF(0)
MOCKABLE_HELPER_DEF(1)
MOCKABLE_HELPER_DEF(2)
MOCKABLE_HELPER_DEF(3)
MOCKABLE_HELPER_DEF(4)
MOCKABLE_HELPER_DEF(5)
MOCKABLE_HELPER_DEF(6)
MOCKABLE_HELPER_DEF(7)
MOCKABLE_HELPER_DEF(8)
MOCKABLE_HELPER_DEF(9)
MOCKABLE_HELPER_DEF(10)
MOCKABLE_HELPER_DEF(11)
MOCKABLE_HELPER_DEF(12)

#define MOCKABLE_HELPER_MF_DEF(n) \
  template<typename R, typename CLS DECL_TEMPLATE_ARGS(n)> \
  PlaceHolder* MockableHelper(R (CLS::*pmf)(DECL_ARGS(n))) {\
    return new RetValueImpl<R>();\
  }

MOCKABLE_HELPER_MF_DEF(0)
MOCKABLE_HELPER_MF_DEF(1)
MOCKABLE_HELPER_MF_DEF(2)
MOCKABLE_HELPER_MF_DEF(3)
MOCKABLE_HELPER_MF_DEF(4)
MOCKABLE_HELPER_MF_DEF(5)
MOCKABLE_HELPER_MF_DEF(6)
MOCKABLE_HELPER_MF_DEF(7)
MOCKABLE_HELPER_MF_DEF(8)
MOCKABLE_HELPER_MF_DEF(9)
MOCKABLE_HELPER_MF_DEF(10)
MOCKABLE_HELPER_MF_DEF(11)
MOCKABLE_HELPER_MF_DEF(12)

struct RetValueHolder
{
   virtual void setValue(const Any& any) = 0;
};

template<typename ValueType>
struct RetValueImpl : public ValueHolderBase<ValueType>, public RetValueHolder
{
    RetValueImpl() : held(0) {}
    ~RetValueImpl()
    {
      if(held) delete held;
    }

    PlaceHolder * clone() const
    {
      RetValueImpl* impl = new RetValueImpl();
      impl->setValue(getValue());
      return impl;
    }

    const ValueType& getValue() const
    {
      MOCKCPP_ASSERT(held != 0);
      return *held;
    }

    void setValue(const ValueType& v)
    {
      if(held) delete held;
      held = new ValueType(v);
    }

    void setValue(const Any& any)
    {
      setValue(any_cast<ValueType>(any));
    }

private:
    ValueType* held;

private:
    RetValueImpl(const RetValueImpl&);
    RetValueImpl& operator=(const RetValueImpl&);
};

struct RetValue {
  RetValue(PlaceHolder* holder) : value(holder), wrap(value) {}

  template<typename RT>
  operator RT() const {
    return any_cast<RT>(wrap);
  }

  void setValue(const Any& any)
  {
    RetValueHolder* holder = dynamic_cast<RetValueHolder*>(value);
    MOCKCPP_ASSERT(holder != 0);
    holder->setValue(any);
  }

  PlaceHolder* value;
  AnyBase wrap;

private:
  RetValue(const RetValue&);
  RetValue& operator=(const RetValue&);
};

#define OVERLAPPED_OPERATORS(ret, op) \
template<typename T>\
ret operator op(T x, RetValue y) { return x op any_cast<T>(y); }\
template<typename T>\
ret operator op(RetValue x, T y) { return any_cast<T>(x) op y; }

OVERLAPPED_OPERATORS(T, +)
OVERLAPPED_OPERATORS(T, -)
OVERLAPPED_OPERATORS(T, *)
OVERLAPPED_OPERATORS(T, /)
OVERLAPPED_OPERATORS(T, %)

OVERLAPPED_OPERATORS(T, ^)
OVERLAPPED_OPERATORS(T, &)
OVERLAPPED_OPERATORS(T, |)

OVERLAPPED_OPERATORS(T, <<)
OVERLAPPED_OPERATORS(T, >>)

OVERLAPPED_OPERATORS(T, +=)
OVERLAPPED_OPERATORS(T, -=)
OVERLAPPED_OPERATORS(T, *=)
OVERLAPPED_OPERATORS(T, /=)
OVERLAPPED_OPERATORS(T, %=)

OVERLAPPED_OPERATORS(T, ^=)
OVERLAPPED_OPERATORS(T, &=)
OVERLAPPED_OPERATORS(T, |=)

OVERLAPPED_OPERATORS(T, <<=)
OVERLAPPED_OPERATORS(T, >>=)

OVERLAPPED_OPERATORS(bool, ==)
OVERLAPPED_OPERATORS(bool, !=)
OVERLAPPED_OPERATORS(bool, <)
OVERLAPPED_OPERATORS(bool, <=)
OVERLAPPED_OPERATORS(bool, >)
OVERLAPPED_OPERATORS(bool, >=)

////////////////////////////////////////////
#define FUNCTOR_DEF(n) \
    template <DECL_VOID_TEMPLATE_ARGS(n)> \
    const RetValue& operator()(DECL_PARAMS_LIST(n)) \
    { \
      return invoke(DECL_PARAMS(n));\
    }

struct Functor
{
   Functor(PlaceHolder* holder, const std::string& fName, const char* cName)
      : ret(holder), name(fName), nameOfCaller(cName) {}

   const RetValue& invoke(const RefAny& p1 = RefAny()
                 , const RefAny& p2 = RefAny()
                 , const RefAny& p3 = RefAny()
                 , const RefAny& p4 = RefAny()
                 , const RefAny& p5 = RefAny()
                 , const RefAny& p6 = RefAny()
                 , const RefAny& p7 = RefAny()
                 , const RefAny& p8 = RefAny()
                 , const RefAny& p9 = RefAny()
                 , const RefAny& p10 = RefAny()
                 , const RefAny& p11 = RefAny()
                 , const RefAny& p12 = RefAny())
   {
      Invokable* invokable = GlobalMockObject::instance.getInvokable(name);
      try {
        SelfDescribe* resultProvider = 0;
        ret.setValue(invokable->invoke(nameOfCaller DECL_REST_PARAMS(12), resultProvider));
      }
      catch(std::exception& ex) {
         MOCKCPP_REPORT_FAILURE(ex.what());
         ret.setValue(Any());
      }
      return ret;
   }

   const RetValue& operator()(void)
   {
     return invoke();
   }
   FUNCTOR_DEF(1)
   FUNCTOR_DEF(2)
   FUNCTOR_DEF(3)
   FUNCTOR_DEF(4)
   FUNCTOR_DEF(5)
   FUNCTOR_DEF(6)
   FUNCTOR_DEF(7)
   FUNCTOR_DEF(8)
   FUNCTOR_DEF(9)
   FUNCTOR_DEF(10)
   FUNCTOR_DEF(11)
   FUNCTOR_DEF(12)

private:
   RetValue ret;
   std::string name;
   std::string nameOfCaller;
};

#ifdef _MSC_VER

  #define MEM_FUNCTOR_DEF(n) \
      template <DECL_VOID_TEMPLATE_ARGS(n)> \
      const RetValue& operator()(DECL_PARAMS_LIST(n)) \
      { \
        return invoke(DECL_PARAMS(n));\
      }

#else

  #define MEM_FUNCTOR_DEF(n) \
      template <DECL_VOID_TEMPLATE_ARGS(n)> \
      const RetValue& operator()(DECL_PARAMS_LIST(n)) \
      { \
        return invoke(obj DECL_REST_PARAMS(n));\
      }

#endif

template<typename CLS>
struct MemFunctor : public Functor
{
   MemFunctor(PlaceHolder* holder, const std::string& fName, const char* cName, CLS* p)
      : Functor(holder, fName, cName), obj(p) {}

   const RetValue& operator()(void)
   {
     return invoke(obj);
   }
   MEM_FUNCTOR_DEF(1)
   MEM_FUNCTOR_DEF(2)
   MEM_FUNCTOR_DEF(3)
   MEM_FUNCTOR_DEF(4)
   MEM_FUNCTOR_DEF(5)
   MEM_FUNCTOR_DEF(6)
   MEM_FUNCTOR_DEF(7)
   MEM_FUNCTOR_DEF(8)
   MEM_FUNCTOR_DEF(9)
   MEM_FUNCTOR_DEF(10)
   MEM_FUNCTOR_DEF(11)

 private:
   CLS* obj;
};

/////////////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif // MOCKCPP_USE_MOCKABLE

#endif

