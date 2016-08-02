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

#include <algorithm>

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

//////////////////////////////////////////
std::string toPointerString(void* p)
{
   if(p == 0) return "NULL";

   oss_t oss;

   oss << "0x";
   oss.flags (std::ios::hex);
   oss.fill('0'); oss.width(8);
   oss << reinterpret_cast<unsigned long>(p);

   return oss.str();
}
//////////////////////////////////////////
std::string toString(std::string s)
{
	oss_t oss;
	oss << "\"" << s << "\"";
	return oss.str();
}

//////////////////////////////////////////
template <typename T>
std::string toPCharStr(const T& s)
{
	oss_t oss;

	if(s == 0)
      oss << "NULL";
	else
#if 0
	  oss << "\"" << s << "\"";
#endif

    oss << (void*) s;

	return oss.str();
}

//////////////////////////////////////////
std::string toString(char* s)
{ return toPCharStr(s); }

//////////////////////////////////////////
std::string toString(const char* s)
{ return toPCharStr(s); }

//////////////////////////////////////////
std::string toString(bool b)
{
	oss_t oss;
	oss << (b?"true":"false");
	return oss.str();
}

//////////////////////////////////////////
template <typename T>
std::string toHexStr(T val)
{
	oss_t oss;
	oss.flags (std::ios::hex | std::ios::showbase);
	oss << val;
   return oss.str();
}

//////////////////////////////////////////
std::string toFixedSizedHexStr(unsigned int i)
{
   oss_t oss;
   oss.flags (std::ios::hex);
   oss.fill('0'); oss.width(2);
   oss << i;

   return oss.str();
}

//////////////////////////////////////////
std::string toFixedSizedHexStr(unsigned char val)
{ return toFixedSizedHexStr((unsigned int)val&0xFF); }

//////////////////////////////////////////
std::string toHexStr(char val)
{ return toHexStr((int)val&0xFF); }

//////////////////////////////////////////
std::string toHexStr(unsigned char val)
{ return toHexStr((unsigned int)val&0xFF); }

//////////////////////////////////////////
std::string toHexStr(short val)
{ return toHexStr((unsigned int)val&0xFFFF); }

//////////////////////////////////////////
std::string toHexStr(int val)
{ return toHexStr((unsigned int)val&0xFFFFFFFF); }

//////////////////////////////////////////
std::string toBufferString(void* buf, size_t size)
{
   oss_t oss;

   size_t sz = std::min(size, size_t(4));

   unsigned char* p = (unsigned char*)buf;

   oss << "[";

   for(size_t i=0; i < sz; i++)
   {
      oss << toFixedSizedHexStr(p[i]);
      if(i != sz - 1)
      {
         oss << " ";
      }
   }

   if(size > size_t(4))
   {
      oss << " ...";
   }

   oss << "]";

   return oss.str();
}
//////////////////////////////////////////
template <typename T>
std::string toValStr(T val)
{
	oss_t oss;
	oss << val;
   return oss.str();
}

//////////////////////////////////////////
std::string toValStr(char val)
{ return toValStr((int)val); }

//////////////////////////////////////////
std::string toValStr(unsigned char val)
{ return toValStr((unsigned int)val); }

//////////////////////////////////////////
template <typename T>
std::string toHexAndDecStr(T val)
{
	oss_t oss;
	oss << toHexStr(val) << "/" << toValStr(val);
	return oss.str();
}

//////////////////////////////////////////
std::string toString(char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(unsigned char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(short s)
{ return toHexAndDecStr(s); }

//////////////////////////////////////////
std::string toString(unsigned short s)
{ return toHexAndDecStr(s); }

//////////////////////////////////////////
std::string toString(int i)
{ return toHexAndDecStr(i); }

//////////////////////////////////////////
std::string toString(unsigned int i)
{ return toHexAndDecStr(i); }

//////////////////////////////////////////
std::string toString(long l)
{ return toHexAndDecStr(l); }

//////////////////////////////////////////
std::string toString(unsigned long l)
{ return toHexAndDecStr(l); }

//////////////////////////////////////////
std::string toString(long long ll)
{ return toHexAndDecStr(ll); }

//////////////////////////////////////////
std::string toString(unsigned long long ll)
{ return toHexAndDecStr(ll); }

//////////////////////////////////////////
std::string toString(float f)
{ return toValStr(f); }

//////////////////////////////////////////
std::string toString(double f)
{ return toValStr(f); }

//////////////////////////////////////////

MOCKCPP_NS_END

