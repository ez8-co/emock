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

#ifndef __EMOCK_H
#define __EMOCK_H


#if !defined(EMOCK_NO_NAMESPACE) || (EMOCK_NO_NAMESPACE == 0)
# define EMOCK_NS emock
# define EMOCK_NS_START namespace EMOCK_NS {
# define EMOCK_NS_END }
# define USING_EMOCK_NS using namespace EMOCK_NS;
#else
# define EMOCK_NS 
# define EMOCK_NS_START 
# define EMOCK_NS_END 
# define USING_EMOCK_NS 
#endif

#ifdef _MSC_VER
# define EMOCK_EXPORT __declspec(dllexport)
# define EMOCK_API __stdcall
#else
# define EMOCK_EXPORT
# define EMOCK_API
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

#endif // __EMOCK_H

