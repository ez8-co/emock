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

#ifndef __MOCKCPP_RESULT_H
#define __MOCKCPP_RESULT_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

struct Any;
struct SelfDescribe;
struct ResultImpl;

struct Result
{
    Result( bool isCastable
          , const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber);

    ~Result();

    const Any& getResult(const Any& result) const;

private:

    ResultImpl* This; 
};

MOCKCPP_NS_END

#endif

