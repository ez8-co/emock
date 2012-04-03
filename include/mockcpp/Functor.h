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

#ifndef __MOCKCPP_FUNCTOR_H
#define __MOCKCPP_FUNCTOR_H

#include <mockcpp/mockcpp.h>

#include <string>

#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

MOCKCPP_NS_START

/////////////////////////////////////////////
struct BaseFunctor
{
   BaseFunctor(const std::string& fName, const char* cName)
      : name(fName), nameOfCaller(cName) {}

   std::string getName() const
   {
      return name;
   }

   std::string getNameOfCaller() const
   {
      return nameOfCaller;
   }

private:
   std::string name;
   std::string nameOfCaller;
};

////////////////////////////////////////////
template <typename F>
struct Functor;

#define FUNCTOR_CONS()  \
    Functor(const std::string& name, const char* cName) \
      : BaseFunctor(name, cName) \
    {}

////////////////////////////////////////////
#define FUNCTOR_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct Functor<R(DECL_ARGS(n))> : public BaseFunctor \
{ \
    FUNCTOR_CONS() \
 \
    R operator()(DECL_PARAMS_LIST(n)) \
    { \
        return GlobalMockObject::instance.invoke<R>(getName()) \
                                    (getNameOfCaller() DECL_REST_PARAMS(n)); \
    } \
}


FUNCTOR_DEF(0);
FUNCTOR_DEF(1);
FUNCTOR_DEF(2);
FUNCTOR_DEF(3);
FUNCTOR_DEF(4);
FUNCTOR_DEF(5);
FUNCTOR_DEF(6);
FUNCTOR_DEF(7);
FUNCTOR_DEF(8);
FUNCTOR_DEF(9);
FUNCTOR_DEF(10);
FUNCTOR_DEF(11);
FUNCTOR_DEF(12);

///////////////////////////////////////////////////////
#define VARDIC_FUNCTOR_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct Functor<R(DECL_VARDIC_ARGS(n) ...)> : public BaseFunctor \
{ \
    FUNCTOR_CONS() \
 \
    R operator()(const RefAny& p1 = RefAny(), const RefAny& p2 = RefAny(), \
         const RefAny& p3 = RefAny(), const RefAny& p4 = RefAny(), \
         const RefAny& p5 = RefAny(), const RefAny& p6 = RefAny(), \
         const RefAny& p7 = RefAny(), const RefAny& p8 = RefAny(), \
         const RefAny& p9 = RefAny(), const RefAny& p10 = RefAny(), \
         const RefAny& p11 = RefAny(), const RefAny& p12 = RefAny()) \
    { \
        return GlobalMockObject::instance.invoke<R>(getName()) \
                                    (getNameOfCaller() DECL_REST_PARAMS(12)); \
    } \
}

VARDIC_FUNCTOR_DEF(0);
VARDIC_FUNCTOR_DEF(1);
VARDIC_FUNCTOR_DEF(2);
VARDIC_FUNCTOR_DEF(3);
VARDIC_FUNCTOR_DEF(4);
VARDIC_FUNCTOR_DEF(5);
VARDIC_FUNCTOR_DEF(6);
VARDIC_FUNCTOR_DEF(7);
VARDIC_FUNCTOR_DEF(8);

/////////////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

