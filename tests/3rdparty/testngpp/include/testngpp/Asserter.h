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

#ifndef __TESTNGPP_ASSERTER_H
#define __TESTNGPP_ASSERTER_H

#include <sstream>
#include <string.h>

#include <testngpp/testngpp.h>
#include <testngpp/utils/Formatter.h>

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////////
#define __TESTNGPP_REPORT_FAILURE(what, failfast) \
      reportFailure(__FILE__, __LINE__, what, failfast)

//////////////////////////////////////////////////////////////////
#define __ASSERT_TRUE(expr, failfast) do { \
   if(!(expr)) {\
      __TESTNGPP_REPORT_FAILURE("expected (" #expr ") being TRUE, but it's actually FALSE", failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __ASSERT_FALSE(expr, failfast) do { \
   if(expr) {\
      __TESTNGPP_REPORT_FAILURE("expected (" #expr ") being FALSE, but it's actually TRUE", failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
template<typename T1, typename T2>
void __testngpp_assert_eq_helper(TestFixture *tf, T1 expected_value, const char* expected_value_name, T2 value, const char* value_name, bool failfast)
{
   if(!(expected_value == value)) {
      std::stringstream ss;
      ss << "expected (" << expected_value_name << "==" << value_name << "), found ("
         << TESTNGPP_NS::toTypeAndValueString(expected_value)
         << "!="
         << TESTNGPP_NS::toTypeAndValueString(value)
         << ")";
      tf->__TESTNGPP_REPORT_FAILURE(ss.str(), failfast);
   }
}

template<typename T1, typename T2>
void __testngpp_assert_ne_helper(TestFixture *tf, T1 expected_value, const char* expected_value_name, T2 value, const char* value_name, bool failfast)
{
   if(!(expected_value != value)) {
      std::stringstream ss;
      ss << "expected (" << expected_value_name << "!=" << value_name << "), found ("
         << TESTNGPP_NS::toTypeAndValueString(expected_value)
         << "=="
         << TESTNGPP_NS::toTypeAndValueString(value)
         << ")";
      tf->__TESTNGPP_REPORT_FAILURE(ss.str(), failfast);
   }
}

//////////////////////////////////////////////////////////////////
#define __ASSERT_EQ(expected, value, failfast) \
	testngpp::__testngpp_assert_eq_helper(this, expected, #expected, value, #value, failfast)

//////////////////////////////////////////////////////////////////
#define __ASSERT_NE(expected, value, failfast) \
	testngpp::__testngpp_assert_ne_helper(this, expected, #expected, value, #value, failfast)

//////////////////////////////////////////////////////////////////
#define __ASSERT_THROWS(expr, except, failfast) do { \
   bool testngpp_caught_exception = false; \
   try { \
      expr; \
   }catch(except&){ \
      testngpp_caught_exception = true; \
   } catch(...) {\
	  __TESTNGPP_REPORT_FAILURE( \
         "expected " #expr " will throw an exception of type " #except \
         ", but actually raised a different kind of exception.", false); \
      throw; /*let user know which exception was throwed.*/\
   } \
   if(!testngpp_caught_exception) { \
      __TESTNGPP_REPORT_FAILURE( \
         "expected " #expr " will throw an exception of type " #except ", but actually not.", failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __ASSERT_THROWS_ANYTHING(expr, failfast) do { \
   bool __testngpp_caught_exception = false; \
   try { \
      expr; \
   }catch(...){ \
      __testngpp_caught_exception = true; \
   } \
   if(!__testngpp_caught_exception) { \
      __TESTNGPP_REPORT_FAILURE ( \
         "expected " #expr " will throw an exception of any type, but actually not.", failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __ASSERT_THROWS_NOTHING(expr, failfast) do { \
   try { \
      expr; \
   }catch(...){ \
      __TESTNGPP_REPORT_FAILURE ( \
          "expected " #expr " will not throw any exceptions, but it actually did.", failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __ASSERT_THROWS_EQ(expr, except, expected, value, failfast) do { \
   try { \
      expr; \
      __TESTNGPP_REPORT_FAILURE ( \
          "expected " #expr " will throw an exception of type " #except ", but actually not.", failfast); \
   }catch(except){ \
      __ASSERT_EQ(expected, value, failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __ASSERT_SAME_DATA(addr1, addr2, size, failfast) do { \
   void* p1 = reinterpret_cast<void*>(addr1); \
   void* p2 = reinterpret_cast<void*>(addr2); \
   if(::memcmp((void*)p1, (void*)p2, size)) \
   { \
      std::stringstream ss; \
      ss << "expected (" #addr1 ", " #addr2 ") have same data, found (" \
         << TESTNGPP_NS::toBufferString(p1, size) \
         << ", " \
         << TESTNGPP_NS::toBufferString(p2, size) \
         << ")"; \
      __TESTNGPP_REPORT_FAILURE(ss.str(), failfast); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __TESTNGPP_ABS(value) ((value) > 0?(value):-(value))
//////////////////////////////////////////////////////////////////
template<typename T, typename T1, typename T2>
void __testngpp_assert_delta_helper(TestFixture *tf, T1 x, const char* x_name, T2 y, const char* y_name, T d, bool failfast)
{
   T actual_delta = __TESTNGPP_ABS(x - y);
   if(actual_delta > d)
   {
      std::stringstream ss;
      ss << "expected the delta of (" << x_name << ", " << y_name << ") <= ("
         << TESTNGPP_NS::toTypeAndValueString(d)
         << "), actual delta: ("
         << TESTNGPP_NS::toTypeAndValueString(actual_delta)
         << ")";
      tf->__TESTNGPP_REPORT_FAILURE(ss.str(), failfast);
   }
}

#define __ASSERT_DELTA(x, y, d, failfast) \
	testngpp::__testngpp_assert_delta_helper(this, x, #x, y, #y, __TESTNGPP_ABS(d), failfast)

//////////////////////////////////////////////////////////////////
#define ASSERT_TRUE(expr) __ASSERT_TRUE(expr, true)
#define ASSERT_FALSE(expr) __ASSERT_FALSE(expr, true)
#define ASSERT_EQ(expected, value) __ASSERT_EQ(expected, value, true)
#define ASSERT_NE(expected, value) __ASSERT_NE(expected, value, true)
#define ASSERT_THROWS(expr, except) __ASSERT_THROWS(expr, except, true)
#define ASSERT_THROWS_ANYTHING(expr) __ASSERT_THROWS_ANYTHING(expr, true)
#define ASSERT_THROWS_NOTHING(expr) __ASSERT_THROWS_NOTHING(expr, true)
#define ASSERT_THROWS_EQ(expr, except, expected, value) \
   __ASSERT_THROWS_EQ(expr, except, expected, value, true)
#define ASSERT_SAME_DATA(addr1, addr2, size) __ASSERT_SAME_DATA(addr1, addr2, size, true)
#define ASSERT_DELTA(x, y, d)  __ASSERT_DELTA(x, y, d, true)

//////////////////////////////////////////////////////////////////
#define EXPECT_TRUE(expr) __ASSERT_TRUE(expr, false)
#define EXPECT_FALSE(expr) __ASSERT_FALSE(expr, false)
#define EXPECT_EQ(expected, value) __ASSERT_EQ(expected, value, false)
#define EXPECT_NE(expected, value) __ASSERT_NE(expected, value, false)
#define EXPECT_THROWS(expr, except) __ASSERT_THROWS(expr, except, false)
#define EXPECT_THROWS_ANYTHING(expr) __ASSERT_THROWS_ANYTHING(expr, false)
#define EXPECT_THROWS_NOTHING(expr) __ASSERT_THROWS_NOTHING(expr, false)
#define EXPECT_THROWS_EQ(expr, except, expected, value) \
   __ASSERT_THROWS_EQ(expr, except, expected, value, false)
#define EXPECT_SAME_DATA(addr1, addr2, size) __ASSERT_SAME_DATA(addr1, addr2, size, false)
#define EXPECT_DELTA(x, y, d)  __ASSERT_DELTA(x, y, d, false)

//////////////////////////////////////////////////////////////////
#define FAIL(msg) do { \
    __TESTNGPP_REPORT_FAILURE(msg, true); \
}while(0)

//////////////////////////////////////////////////////////////////
#define WARN(msg) do { \
    reportWarning(__FILE__, __LINE__, msg); \
}while(0)

//////////////////////////////////////////////////////////////////
#define INFO(msg) do { \
    reportInfo(__FILE__, __LINE__, msg); \
}while(0)


//////////////////////////////////////////////////////////////////
struct DoingWell {};
#define __DO__        try {
#define __CLEANUP__   throw TESTNGPP_NS::DoingWell(); } catch(...) {
#define __DONE__      try {throw;}catch(TESTNGPP_NS::DoingWell&){}} 

//////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

