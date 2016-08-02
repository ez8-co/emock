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

#ifndef MOCKCPP_IS_REF_H
#define MOCKCPP_IS_REF_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

//////////////////////////////////////////
template <typename T>
struct IsRef
{
	static const bool isTrue = false;
	static const bool outBoundable = false;
};

//////////////////////////////////////////
template <typename T>
struct IsRef<T&>
{
	static const bool isTrue = true;
	static const bool outBoundable = true;
};

//////////////////////////////////////////
template <typename T>
struct IsRef<const T&>
{
	static const bool isTrue = true;
	static const bool outBoundable = false;
};

//////////////////////////////////////////

MOCKCPP_NS_END


#endif 

