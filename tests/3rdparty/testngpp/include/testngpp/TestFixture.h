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

#ifndef __TESTNGPP_FIXTURE_H
#define __TESTNGPP_FIXTURE_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCaseInfoReader;
struct TestCaseResultCollector;

struct TestFixture
{
   TestFixture() : testcase(0), collector(0) {}

	virtual void setUp() {}
	virtual void tearDown() {}

   virtual ~TestFixture() {}

   //////////////////////////////////////////////
   void reportInfo(const char* file, unsigned int line, const std::string& info);
   void reportWarning(const char* file, unsigned int line, const std::string& warning);
   void reportFailure(const char* file, unsigned int line, const std::string& failure, bool throwException=true);

   //////////////////////////////////////////////
   void setCurrentTestCase(const TestCaseInfoReader*, TestCaseResultCollector*);
   TestFixture *clone();

private:

   const TestCaseInfoReader* testcase;
   TestCaseResultCollector* collector;
};

TESTNGPP_NS_END

#endif

