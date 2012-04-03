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

#include <testngpp/internal/TestSuiteDesc.h>
#include <testngpp/internal/TestFixtureDesc.h>

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////
const unsigned int
TestSuiteDesc::getNumberOfTestCases() const
{
   unsigned int numberOfTestCases = 0;

   for(unsigned int i=0; i<numberOfFixtures; i++)
   {
      numberOfTestCases += getTestFixture(i)->getNumberOfTestCases();
   }

   return numberOfTestCases;
}

//////////////////////////////////////////////////////////////
TestFixtureDesc*
TestSuiteDesc::getTestFixture(unsigned int index) const
{
   if(index >= numberOfFixtures)
   {
      return 0;
   }

   return testFixtures[index];
}

//////////////////////////////////////////////////////////////

TESTNGPP_NS_END
