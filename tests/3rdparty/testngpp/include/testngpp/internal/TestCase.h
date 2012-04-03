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

#ifndef __TESTNGPP_TEST_CASE_H
#define __TESTNGPP_TEST_CASE_H

#include <testngpp/testngpp.h>
#include <string>

#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/TestFixture.h>
#include <testngpp/runner/loaders/ModuleLoader.h>

TESTNGPP_NS_START

struct TestCase
   : public TestCaseInfoReader
{
	TestCase( const std::string& nameOfCase
           , const std::string& nameOfFixture
		     , const std::string& nameOfSuite
           , TESTNGPP_NS::TestCase* testcase
           , const std::string& file
           , unsigned int line)
	  : name(nameOfCase)
      , fixtureName(nameOfFixture)
	  , suiteName(nameOfSuite)
      , depends(testcase)
      , fileName(file)
      , lineOfFile(line)
      , fixtureCloneAsReporter(0)
   {}

	virtual ~TestCase() { delete fixtureCloneAsReporter; }

	const std::string& getName() const
	{ return name; }

	const std::string& getNameOfFixture() const
	{ return fixtureName; }

	const std::string& getNameOfSuite() const
	{ return suiteName; }
	
    TESTNGPP_NS::TestCase* 
    getDependedTestCase() const
    { return depends; }

	const std::string& getFileName() const
	{ return fileName; }

	const unsigned int getLineOfFile() const
	{ return lineOfFile; }

   virtual TESTNGPP_NS::TestFixture* getFixture() const = 0;
   virtual void setFixture(TESTNGPP_NS::TestFixture* fixture = 0) = 0;

   void setUp()
   {
       startMemChecker();
       getFixture()->setUp();
   }

   void tearDown()
   {
      TestFixture * fixture = getFixture();
      fixture->tearDown(); 
      delete fixture;
      verifyMemChecker();      
   }

   void run()
   {
      runDependedTestCase();
      runTest();
   }

   virtual void runTest() = 0;

   unsigned int numberOfTags() const { return 0; }

   const char** getTags() const
   {
     static const char* tags[1] = {0};
     return tags;
   }
   
   void setModuleLoader(ModuleLoader* _loader)
   {
       loader = _loader;
   }

private:
   void startMemChecker();   
public:
   void verifyMemChecker()
   {    
     	typedef void (*verify_t)(void);    
    	verify_t verifier = (verify_t)loader->findSymbol("verifyMemChecker");    
    	verifier(); 
   }

private:

   void runDependedTestCase()
   {
      if(depends == 0)
         return;

      depends->setFixture(getFixture());
      depends->run();
   }

private:
	std::string name;
	std::string fixtureName;
	std::string suiteName;
   TESTNGPP_NS::TestCase* depends;
   std::string fileName;
	unsigned int lineOfFile;
	ModuleLoader* loader;
    TestFixture *fixtureCloneAsReporter;
};

TESTNGPP_NS_END

#endif

