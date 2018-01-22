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

#ifndef __MOCKCPP_H
#define __MOCKCPP_H


#if !defined(MOCKCPP_NO_NAMESPACE) || (MOCKCPP_NO_NAMESPACE == 0)
# define MOCKCPP_NS mockcpp
# define MOCKCPP_NS_START namespace MOCKCPP_NS {
# define MOCKCPP_NS_END }
# define USING_MOCKCPP_NS using namespace MOCKCPP_NS;
#else
# define MOCKCPP_NS 
# define MOCKCPP_NS_START 
# define MOCKCPP_NS_END 
# define USING_MOCKCPP_NS 
#endif

#ifdef _MSC_VER
# define MOCKCPP_EXPORT __declspec(dllexport)
# define MOCKCPP_API __stdcall
#else
# define MOCKCPP_EXPORT
# define MOCKCPP_API
#endif


#if  ( defined (__LP64__) \
    || defined (__64BIT__) \
    || defined (_LP64) \
    || ((defined(__WORDSIZE)) && (__WORDSIZE == 64)) \
	|| defined(WIN64))

#define BUILD_FOR_X64 1
#define BUILD_FOR_X86 0

#else	

#define BUILD_FOR_X64 0
#define BUILD_FOR_X86 1

#endif

#endif // __MOCKCPP_H

