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

#ifndef __TESTNGPP_XML_TEST_LISTENER_H
#define __TESTNGPP_XML_TEST_LISTENER_H

#include <testngpp/testngpp.h>
#include <testngpp/listener/TestListener.h>
#include <sstream>

TESTNGPP_NS_START

struct TestSuiteInfoReader;
struct TestResultReporter;
struct TestSuiteResultReporter;
struct TestCaseResultReporter;
struct XMLTestListenerImpl;

struct XMLTestListener
   : public TestListener
{
   XMLTestListener( TestResultReporter*
                     , TestSuiteResultReporter*
                     , TestCaseResultReporter*
                     , std::ostream& os);
   ~XMLTestListener();

   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase
            ( const TestCaseInfoReader*
            , unsigned int
            , unsigned int);

   void startTestFixture(TestFixtureInfoReader*);
   void endTestFixture(TestFixtureInfoReader*);
   void addFixtureError(TestFixtureInfoReader*, const std::string&);
   void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&);

   void startTestSuite(TestSuiteInfoReader*);
   void endTestSuite(TestSuiteInfoReader*);

   void addSuiteError(TestSuiteInfoReader*, const std::string&);

   void startTagsFiltering(const TagsFilterRule*);
   void endTagsFiltering(const TagsFilterRule*);

   void startTest();
   void endTest(unsigned int, unsigned int);
   void addError(const std::string&);

private:

	XMLTestListenerImpl* This;
};

TESTNGPP_NS_END

#endif
