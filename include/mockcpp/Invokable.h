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

#ifndef __MOCKCPP_INVOKABLE_H
#define __MOCKCPP_INVOKABLE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Any.h>
#include <mockcpp/types/RefAny.h>

#include <string>

MOCKCPP_NS_START

///////////////////////////////////////////////
struct SelfDescribe;

///////////////////////////////////////////////
struct Invokable
{
    virtual const Any&
        invoke( const std::string& nameOfCaller
              , const RefAny& p1
              , const RefAny& p2
              , const RefAny& p3
              , const RefAny& p4
              , const RefAny& p5
              , const RefAny& p6
              , const RefAny& p7
              , const RefAny& p8
              , const RefAny& p9
              , const RefAny& p10
              , const RefAny& p11
              , const RefAny& p12
              , SelfDescribe* &resultProvider) = 0;

    
    virtual ~Invokable() {}
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

