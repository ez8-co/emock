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

#ifndef __TESTNGPP_TEST_SUITE_DESC_H
#define __TESTNGPP_TEST_SUITE_DESC_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/internal/TestSuiteInfoReader.h>

TESTNGPP_NS_START

struct TestFixtureDesc;

struct TestSuiteDesc
   : public TestSuiteInfoReader
{
   TestSuiteDesc(const std::string& name
                  , TestFixtureDesc** arrayOfTestFixtures
                  , unsigned int sizeOfArray)
      : nameOfSuite(name)
      , testFixtures(arrayOfTestFixtures)
      , numberOfFixtures(sizeOfArray)
      , fileName("")
   {}

   const std::string& getName() const
   { return nameOfSuite; }

   const std::string& getFileName() const
   { return fileName; }

   const unsigned int getNumberOfTestFixtures() const
   { return numberOfFixtures; }

   void setFileName(const std::string name)
   { fileName = name; }

   const unsigned int getNumberOfTestCases() const;
   TestFixtureDesc* getTestFixture(unsigned int index) const;

private:
   std::string nameOfSuite;
   TestFixtureDesc** testFixtures;
   unsigned int numberOfFixtures;
   std::string fileName;
};

TESTNGPP_NS_END

#endif

