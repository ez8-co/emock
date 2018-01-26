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

#ifndef __EMOCK_FORMATTER_H
#define __EMOCK_FORMATTER_H

#include <emock/emock.h>

#include <string>

#include <emock/OutputStringStream.h>
#include <emock/TypeString.h>

EMOCK_NS_START

///////////////////////////////////////////////////////
std::string toBufferString(void* buf, size_t size);

///////////////////////////////////////////////////////
template <typename T>
std::string toString(const T& val)
{
   return EMOCK_NS::toBufferString((void*)&val, sizeof(val));
}

///////////////////////////////////////////////////////
std::string toPointerString(void*);

///////////////////////////////////////////////////////
template <typename T>
std::string toString(T* p)
{
   return EMOCK_NS::toPointerString((void*)p);
}

///////////////////////////////////////////////////////
template <typename T>
std::string toString(const T* s)
{
	return EMOCK_NS::toPointerString((void*)s);
}

///////////////////////////////////////////////////////
std::string toString(std::string s);
std::string toString(char* s);
std::string toString(const char* s);
std::string toString(float f);
std::string toString(double d);
std::string toString(bool b);
std::string toString(char c);
std::string toString(unsigned char c);
std::string toString(short s);
std::string toString(unsigned short s);
std::string toString(int i);
std::string toString(unsigned int i);
std::string toString(long l);
std::string toString(unsigned long l);

#if (EMOCK_SUPPORT_LONG_LONG == 1)
std::string toString(long long ll);
std::string toString(unsigned long long ll);
#endif

/////////////////////////////////////////////////////////////////
template <typename T>
std::string toTypeAndValueString(const T& val)
{
	oss_t oss;
	oss << "(" << EMOCK_NS::TypeString<T>::value() << ")" 
       << EMOCK_NS::toString(val);
	return oss.str();
}

EMOCK_NS_END

#endif

