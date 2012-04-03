/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <sstream>
#include <algorithm>

#include <testngpp/utils/Formatter.h>

TESTNGPP_NS_START

//////////////////////////////////////////
std::string toPointerString(void* p)
{
   if(p == 0) return "NULL";

   std::stringstream ss;

   ss << "0x";
   ss.flags (std::ios::hex);
   ss.fill('0'); ss.width(8);
   ss << reinterpret_cast<unsigned long>(p);

   return ss.str();
}
//////////////////////////////////////////
std::string toString(std::string s)
{
	std::stringstream ss;
	ss << "\"" << s << "\"";
	return ss.str();
}

//////////////////////////////////////////
template <typename T>
std::string toPCharStr(const T& s)
{
	std::stringstream ss;

	if(s == 0)
      ss << "NULL";
	else
#if 1
	  ss << "\"" << s << "\"";
#endif

//    ss << (void*) s;

	return ss.str();
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
	std::stringstream ss;
	ss << (b?"true":"false");
	return ss.str();
}

//////////////////////////////////////////
template <typename T>
std::string toHexStr(T val)
{
	std::stringstream ss;
	ss.flags (std::ios::hex | std::ios::showbase);
	ss << val;
   return ss.str();
}

//////////////////////////////////////////
std::string toFixedSizedHexStr(unsigned int i)
{
   std::stringstream ss;
   ss.flags (std::ios::hex);
   ss.fill('0'); ss.width(2);
   ss << i;

   return ss.str();
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
   std::stringstream ss;

   size_t sz = std::min(size, size_t(4));

   unsigned char* p = (unsigned char*)buf;

   ss << "[";

   for(size_t i=0; i < sz; i++)
   {
      ss << toFixedSizedHexStr(p[i]);
      if(i != sz - 1)
      {
         ss << " ";
      }
   }

   if(size > size_t(4))
   {
      ss << " ...";
   }

   ss << "]";

   return ss.str();
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
	std::stringstream ss;
	ss << toHexStr(val) << "/" << toValStr(val);
	return ss.str();
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

TESTNGPP_NS_END

