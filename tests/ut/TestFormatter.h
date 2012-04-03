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

#include <testcpp/testcpp.hpp>
#include <mockcpp/Formatter.h>
#include <stdio.h>

USING_MOCKCPP_NS

class TestFormatter : public TESTCPP_NS::TestFixture
{
public:
   void setUp() { }
   void tearDown() { }

   /////////////////////////////////////////////////////////

   struct ST { int a, b, c; };

   void testShouldShowMaximum4BytesOfMemory()
   {
      ST st;
      st.a = 0xabcdef00;
      st.b = 0x12345678;
      st.c = 0x09876543;

      std::string expected = "(" + getDemangledName(typeid(st)) + ")[00 ef cd ab ...]";
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(st));
   }

   struct A { A(char v):c(v){} char c; };

   void testShouldBeAbleToStringnizeConstReference()
   {
      A a(5);
      const A& ref = a;

      std::string expected = "(" + getDemangledName(typeid(a)) + ")[05]";
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(ref));
   }

   void testShouldBeAbleToStringnizeReference()
   {
      A a(0xab);
	
      A& ref = a;

      std::string expected = "(" + getDemangledName(typeid(a)) + ")[ab]";
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(ref));
   }

   void testShouldBeAbleToStringnizeConstObject()
   {
      const A p = A(0x3f);	

      std::string expected = "(" + getDemangledName(typeid(p)) + ")[3f]";
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
   }

   void testShouldBeAbleToStringnizeObject()
   {
      A p(8);

      std::string expected = "(" + getDemangledName(typeid(p)) + ")[08]";
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
   }

   void testShouldBeAbleToStringnizeNullObjectAddr()
   {
      A* p = 0;	
#ifdef _MSC_VER
#ifdef WIN64
      std::string expected = "(" + getDemangledName(typeid(A)) + " * __ptr64)NULL";
#else
	  std::string expected = "(" + getDemangledName(typeid(A)) + " *)NULL";
#endif
#else
      std::string expected = "(" + getDemangledName(typeid(A)) + "*)NULL";
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
   }

   void testShouldBeAbleToStringnizeObjectAddr()
   {
      A* p = (A*)0x12ab;	
#ifdef _MSC_VER
#ifdef WIN64
      std::string expected = "(" + getDemangledName(typeid(A)) + " * __ptr64)0x000012ab";
#else
      std::string expected = "(" + getDemangledName(typeid(A)) + " *)0x000012ab";
#endif	  
#else
      std::string expected = "(" + getDemangledName(typeid(A)) + "*)0x000012ab";
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
   }

   void testShouldBeAbleToStringnizeConstObjectAddr()
   {
      const A* p = (const A*)0x12ab;	
#ifdef _MSC_VER
#ifdef WIN64
      std::string expected = std::string("(") + getDemangledName(typeid(A)) + " const * __ptr64)0x000012ab";
#else
      std::string expected = std::string("(") + getDemangledName(typeid(A)) + " const *)0x000012ab";
#endif

#else
      std::string expected = std::string("(") + getDemangledName(typeid(A)) + " const*)0x000012ab";
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
   }

   void testShouldBeAbleToStringnizeString()
   {
      std::string str("abc");
      std::string expected("(std::string)\"abc\"");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(str));
   }

   void testShouldBeAbleToStringnizePChar()
   {
      char* s = (char*)"abc";
      oss_t oss;
#ifdef _MSC_VER
#ifdef WIN64
      oss << "(char * __ptr64)" << (void*)s ;
#else
      oss << "(char *)" << (void*)s ;
#endif
#else
	  oss << "(char*)" << (void*)s ;
#endif
      TS_ASSERT_EQUALS(oss.str(), toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeConstPChar()
   {
      const char* s = "abc";
      oss_t oss;
#ifdef _MSC_VER
#ifdef WIN64
      oss << "(char const * __ptr64)" << (void*)s ;
#else
      oss << "(char const *)" << (void*)s ;
#endif
#else
	  oss << "(char const*)" << (void*)s ;
#endif
      TS_ASSERT_EQUALS(oss.str(), toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeNullPChar()
   {
      char* s = 0;
#ifdef _MSC_VER
#ifdef WIN64
      std::string expected("(char * __ptr64)NULL");
#else
      std::string expected("(char *)NULL");
#endif
#else
	  std::string expected("(char*)NULL");
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeNullConstPChar()
   {
      const char* s = 0;
#ifdef _MSC_VER
#ifdef WIN64
      std::string expected("(char const * __ptr64)NULL");
#else
      std::string expected("(char const *)NULL");
#endif
#else
	  std::string expected("(char const*)NULL");
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeDouble()
   {
      double d = 123.45;
      std::string expected("(double)123.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeNegativeDouble()
   {
      double d = -123.45;
      std::string expected("(double)-123.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeZeroDotDouble()
   {
      double d = 0.45;
      std::string expected("(double)0.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeDotDouble()
   {
      double d = .45;
      std::string expected("(double)0.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeVerySmallDouble()
   {
      double d = .0000000000000000000001;
#ifdef _MSC_VER
      std::string expected("(double)1e-022");
#else
	  std::string expected("(double)1e-22");
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeFloat()
   {
      float f = 123.45;
      std::string expected("(float)123.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
   }

   void testShouldBeAbleToStringnizeConstFloat()
   {
      const float f = 123.45;
      std::string expected("(float)123.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
   }

   void testShouldBeAbleToStringnizeNegativeFloat()
   {
      float f = -123.45;
      std::string expected("(float)-123.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
   }

   void testShouldBeAbleToStringnizeZeroDotFloat()
   {
      float f = 0.45;
      std::string expected("(float)0.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
   }

   void testShouldBeAbleToStringnizeDotFloat()
   {
      float f = .45;
      std::string expected("(float)0.45");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
   }

   void testShouldBeAbleToStringnizeVerySmallFloat()
   {
      float f = .0000000000000000000001;
#ifdef _MSC_VER
      std::string expected("(float)1e-022");
#else
	  std::string expected("(float)1e-22");
#endif
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
   }

   void testShouldBeAbleToStringnizeChar()
   {
      char c = 0x12;
      std::string expected("(char)0x12/18");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
   }

   void testShouldBeAbleToStringnizeConstChar()
   {
      const char c = 0x12;
      std::string expected("(char)0x12/18");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
   }

   void testShouldBeAbleToStringnizeUnsignedChar()
   {
      unsigned char c = 0xa;
      std::string expected("(unsigned char)0xa/10");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
   }

   void testShouldBeAbleToStringnizeNegativeChar()
   {
      char c = -1;
      std::string expected("(char)0xff/-1");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
   }

   void testShouldBeAbleToStringnizeShort()
   {
      short s = 0x12;
      std::string expected("(short)0x12/18");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeUnsignedShort()
   {
      unsigned short s = 0x12;
      std::string expected("(unsigned short)0x12/18");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeNegativeShort()
   {
      short s = -1;
      std::string expected("(short)0xffff/-1");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
   }

   void testShouldBeAbleToStringnizeInt()
   {
      std::string expected("(int)0x4d2/1234");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(1234));
   }

   void testShouldBeAbleToStringnizeUnsignedInt()
   {
      unsigned int i = 1234;
      std::string expected("(unsigned int)0x4d2/1234");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(i));
   }

   void testShouldBeAbleToStringnizeNegativeInt()
   {
      int i = -1234;

      char buf[50];
      ::sprintf(buf, "(int)0x%x/%d", i, i);
		std::string expected(buf);

      TS_ASSERT_EQUALS(expected, toTypeAndValueString(i));
   }
   
   void testShouldBeAbleToStringnizeLong()
   {
      long l = 1234;

      char buf[50];
      ::sprintf(buf, "(long)0x%lx/%ld", l, l);
		std::string expected(buf);

      TS_ASSERT_EQUALS(expected, toTypeAndValueString(l));
   }

   void testShouldBeAbleToStringnizeUnsignedLong()
   {
      unsigned long l = 1234;

      char buf[50];
      ::sprintf(buf, "(unsigned long)0x%lx/%ld", l, l);
		std::string expected(buf);
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(l));
   }

   void testShouldBeAbleToStringnizeNegativeLong()
   {
      long l = -1234;

      char buf[50];
      ::sprintf(buf, "(long)0x%lx/%ld", l, l);
		std::string expected(buf);

      TS_ASSERT_EQUALS(expected, toTypeAndValueString(l));
   }

   void testShouldBeAbleToStringnizeLongLong()
   {
#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
      long long ll = 1234;
      std::string expected("(long long)0x4d2/1234");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(ll));
#endif
   }

   void testShouldBeAbleToStringnizeUnsignedLongLong()
   {
#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
      unsigned long long ll = 1234;
      std::string expected("(unsigned long long)0x4d2/1234");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(ll));
#endif
   }

   void testShouldBeAbleToStringnizeNegativeLongLong()
   {
#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
      long long ll = -1234;
      std::string expected("(long long)0xfffffffffffffb2e/-1234");
      TS_ASSERT_EQUALS(expected, toTypeAndValueString(ll));
#endif
   }
};

