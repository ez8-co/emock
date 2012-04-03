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

#ifndef __TESTNGPP_TEST_FIXTURE_DESC_H
#define __TESTNGPP_TEST_FIXTURE_DESC_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/TestFixture.h>

TESTNGPP_NS_START

struct TestCase;

struct TestFixtureDesc
   : public TestFixtureInfoReader
{
   TestFixtureDesc( const std::string& fixtureName
                  , const std::string fileName
                  , TestCase** arrayOfTestCases
                  , unsigned int sizeOfArray)
      : nameOfFixture(fixtureName)
      , nameOfFile(fileName)
      , testCases(arrayOfTestCases)
      , numberOfTestCases(sizeOfArray)
   {}

   const std::string& getName() const
   { return nameOfFixture; }

   const std::string& getFileName() const
   { return nameOfFile; }

   const unsigned int getNumberOfTestCases() const
   { return numberOfTestCases; }

   TestCase* getTestCase(unsigned int index) const
   {
      if(index >= numberOfTestCases)
      {
         return 0;
      }

      return testCases[index];
   }

private:
   std::string nameOfFixture;
   std::string nameOfFile;
   TestCase** testCases;
   unsigned int numberOfTestCases;
};

TESTNGPP_NS_END

#endif

