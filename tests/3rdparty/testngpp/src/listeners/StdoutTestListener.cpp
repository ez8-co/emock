
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <testngpp/internal/Error.h>
#include <testngpp/internal/AssertionFailure.h>

#include <testngpp/utils/OptionList.h>
#include <testngpp/utils/StringList.h>
#include <testngpp/utils/ConsoleState.h>
#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestSuiteInfoReader.h>
#include <testngpp/internal/TagsFilterRule.h>

#include <testngpp/listener/TestResultReporter.h>
#include <testngpp/listener/TestSuiteResultReporter.h>
#include <testngpp/listener/TestCaseResultReporter.h>

#include <testngpp/listener/TestListener.h>

TESTNGPP_NS_START

namespace
{

   const unsigned int maxLenOfLine = 60;

   enum StateTitle
   {
      ST_SUCCESS,
      ST_INFO,
      ST_WARNING,
      ST_FAILED,
      ST_ERROR,
      ST_CRASHED,
      ST_SKIPPED,
      ST_RUN
   };

   std::string
   formatTitle
      ( const std::string title
      , char pad
      , unsigned int maxLen)
   {
      unsigned int numberOfPadding = maxLen - title.size();
      if(title.size() > maxLen)
      {
         numberOfPadding = 0;
      }

      std::string leftPadding("");
      for(unsigned int i=0; i<numberOfPadding/2; i++)
      {
         leftPadding += pad;
      }

      std::string rightPadding("");
      for(unsigned int i=0; i<numberOfPadding/2+numberOfPadding%2; i++)
      {
         rightPadding = pad + rightPadding;
      }

      return leftPadding + title + rightPadding;
   }

   std::string
   getTitle(const std::string title)
   {
      return '[' + formatTitle(title, ' ', 10) + "] ";
   }   

   std::string
   getTitle(StateTitle code)
   {
      switch(code)
      {
      case ST_SUCCESS:
         return getTitle("OK");
      case ST_ERROR:
         return getTitle("ERROR");
      case ST_CRASHED:
         return getTitle("CRASHED");
      case ST_SKIPPED:
         return getTitle("SKIPPED");
      case ST_FAILED:
         return getTitle("FAILED");
      case ST_WARNING:
         return getTitle("WARNING");
      case ST_INFO:
         return getTitle("INFO");
      case ST_RUN:
         return getTitle("RUN");
      }

      return getTitle("UNKNOWN");
   }

   struct TestCaseResult
   {
      TestCaseResult
         (const TestCaseInfoReader* testcase
         , StateTitle resultCode)
         : name(testcase->getName())
         , fixture(testcase->getNameOfFixture())
         , suite(testcase->getNameOfSuite())
         , result(resultCode)
      {}

      std::string toString() const
      {
          return getTitle(result) + suite + "::" + fixture + "::" + name;
      }
      
      std::string name;
      std::string fixture;
      std::string suite;
      StateTitle result;
   };

   std::string getFileName(std::string file)
   {
       if (file == "")
       {
          return "NULL";
       }
   
       return file.substr(file.find_last_of("/\\")  + 1);
   }
}

///////////////////////////////////////////////////////////
struct StdoutTestListener : public TestListener
{
   StdoutTestListener
      ( bool 
      , bool 
      , bool
      , bool
      , bool
      , unsigned int
      , TestResultReporter*
      , TestSuiteResultReporter*
      , TestCaseResultReporter* );
   
   ///////////////////////////////////////////////////////////
   void addCaseWarning(const TestCaseInfoReader*, const Warning& );
   void addCaseInfo(const TestCaseInfoReader*, const Info& );

   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);
   
   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);
   
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
   
   void showFixtureName(const TestCaseInfoReader*);
   void showSuiteName(const TestCaseInfoReader*);
   void showTagsSpec();

   void reportSuitesResult();
   void reportCasesResult();
   void reportFixturesResult();

   template <typename State>
   void reportNumber
         ( const std::string& title
         , const State& state
         , unsigned int number);
   
   template <typename State>
   void reportCaseMessage
         ( const TestCaseInfoReader* testcase
         , const State& state
         , StateTitle result
         , const std::string& file
         , unsigned int line
         , const std::string& msg);

   template <typename State>
   void reportCaseMessage
         ( const TestCaseInfoReader* testcase
         , const State& state
         , StateTitle result
         , const std::string& msg);
   
   void reportCaseFailure
            ( const TestCaseInfoReader* testcase
            , StateTitle title
            , const std::string& msg);

   void reportCaseFailure
            ( const TestCaseInfoReader* testcase
            , StateTitle title
            , const std::string& file
            , unsigned int line
            , const std::string& msg);

   template <typename State>
   void outputCaseState
            ( const TestCaseInfoReader* testcase
            , const State& state
            , StateTitle title);

   void reportCaseSuccess
         ( const TestCaseInfoReader* testcase
         , unsigned int secs
         , unsigned int usecs);

   void reportAllUnsuccessfulTests() const;

   void addTestResult
         ( std::vector<TestCaseResult>& set
         , const TestCaseInfoReader* testcase
         , StateTitle result );

public:
   std::ostream& outputTestCaseInfo
         (std::ostream&, const TestCaseInfoReader*) const;

private:   
   
   SuccState    succ;
   FailState    fail;
   InfoState    info;
   WarnState    warn;
   DebugState   debug;
   NormalState  normal;

   bool showSuite;
   bool showFixture;
   bool showTags;
   bool verbose;

   bool newFixture;
   bool newSuite;
   bool newTags;
   
   bool isSuccess;

   unsigned int level;

   TestResultReporter*        bookKeeper;      // X
   TestSuiteResultReporter*   suiteBookKeeper; // X
   TestCaseResultReporter*    caseBookKeeper;  // X

   std::vector<TestCaseResult> failedTests;
   std::vector<TestCaseResult> errorTests;
   std::vector<TestCaseResult> crashedTests;
   std::vector<TestCaseResult> skippedTests;

   std::string tags;
};

namespace
{
   struct TestCaseInfo
   {
      TestCaseInfo
         ( const StdoutTestListener* listener
         , const TestCaseInfoReader* test)
         : This(listener)
         , testcase(test)
      {}

      std::ostream& output(std::ostream& os) const
      {
         return This->outputTestCaseInfo(os, testcase);
      }

      const StdoutTestListener* This;
      const TestCaseInfoReader* testcase;
   };
}

///////////////////////////////////////////////////////////
std::ostream& operator<<
      ( std::ostream& os
      , const TestCaseInfo& testcase)
{
   return testcase.output(os);
}
///////////////////////////////////////////////////////////
StdoutTestListener::
StdoutTestListener
      ( bool isColorful
      , bool shouldShowSuite
      , bool shouldShowFixture
      , bool shouldShowTags
      , bool isTest
      , unsigned int reportLevel
      , TestResultReporter* reporter
      , TestSuiteResultReporter* suiteReporter 
      , TestCaseResultReporter* caseReporter)
: succ(isColorful)
, fail(isColorful)
, info(isColorful)
, warn(isColorful)
, debug(isColorful)
, normal(isColorful)
, showSuite(shouldShowSuite)
, showFixture(shouldShowFixture)
, showTags(shouldShowTags)
, verbose(isTest)
, newFixture(false)
, newSuite(false)
, newTags(false)
, isSuccess(false)
, level(reportLevel)
, bookKeeper(reporter)
, suiteBookKeeper(suiteReporter)
, caseBookKeeper(caseReporter)
{
}



///////////////////////////////////////////////////////////
std::ostream&
StdoutTestListener::
outputTestCaseInfo
      ( std::ostream& os
      , const TestCaseInfoReader* testcase) const
{
   if(!showFixture)
   {
      if(!showSuite)
      {
         os << testcase->getNameOfSuite()
            << "::";
      }

      os << testcase->getNameOfFixture()
         << "::";
   }

   os << testcase->getName();

   return os;
}
///////////////////////////////////////////////////////////
template <typename State>
void
StdoutTestListener::
reportCaseMessage
      ( const TestCaseInfoReader* testcase
      , const State& state
      , StateTitle title
      , const std::string& file
      , unsigned int line
      , const std::string& msg)
{
   if(isSuccess && !verbose)
   {
      std::cout << std::endl;
      isSuccess = false;
   }

   std::cout
      << state
      << getTitle(title)
      << normal;

   if(!verbose)
   {
      std::cout
         << info
         << TestCaseInfo(this, testcase)
         << normal;
   }

   if(msg.size() > 0)
   {
      if(!verbose)
      {
         std::cout << " - ";
      }

      std::cout
         << getFileName(file)  //testcase->getFileName()
         << ":"
         << line
         << ": "
         << msg;
   }

   std::cout << std::endl;
}

///////////////////////////////////////////////////////////
template <typename State>
void
StdoutTestListener::
outputCaseState
       ( const TestCaseInfoReader* testcase
       , const State& state
       , StateTitle title)
{
   reportCaseMessage
         ( testcase
         , state
         , title
         , ""
         , 0
         , "");
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
reportCaseSuccess
      ( const TestCaseInfoReader* testcase
      , unsigned int secs
      , unsigned int usecs )
{
   isSuccess = true;

   if(verbose)
   {
      std::cout << succ << getTitle(ST_SUCCESS) << "(";
      if(secs > 0)
         std::cout << secs << "s ";

      std::cout << usecs << " us)" << normal << std::endl;
   }
   else
   {
      std::cout << succ << "." << normal;
      std::cout.flush();
   }
}
///////////////////////////////////////////////////////////
template <typename State>
void
StdoutTestListener::
reportCaseMessage
      ( const TestCaseInfoReader* testcase
      , const State& state
      , StateTitle title
      , const std::string& msg)
{
   reportCaseMessage(testcase, state, title, testcase->getFileName(), testcase->getLineOfFile(), msg);
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
reportCaseFailure
      ( const TestCaseInfoReader* testcase
      , StateTitle title
      , const std::string& msg)
{
   reportCaseMessage(testcase, fail, title, msg);
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
reportCaseFailure
      ( const TestCaseInfoReader* testcase
      , StateTitle title
      , const std::string& file
      , unsigned int line
      , const std::string& msg)
{
   reportCaseMessage
         ( testcase
         , fail
         , title
         , file
         , line
         , msg);
}
///////////////////////////////////////////////////////////
void
StdoutTestListener::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   reportCaseFailure
      ( testcase
      , ST_CRASHED
      , "test crashed unexpectedly.");
}

///////////////////////////////////////////////////////////
void 
StdoutTestListener::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   if(level > 2) return;

   reportCaseMessage
      ( testcase 
      , warn
      , ST_SKIPPED
      , "test was skipped due to the failure of its dependent case.");
}

///////////////////////////////////////////////////////////
void 
StdoutTestListener::
addCaseError
   ( const TestCaseInfoReader* testcase
   , const std::string& error)
{
   reportCaseFailure
      ( testcase
      , ST_ERROR
      , error);
}

///////////////////////////////////////////////////////////
void 
StdoutTestListener::
addCaseFailure
   ( const TestCaseInfoReader* testcase
   , const AssertionFailure& failure)
{
   reportCaseFailure
      ( testcase
      , ST_FAILED
      , failure.getFileName()
      , failure.getLineOfFile()
      , failure.what());
}


///////////////////////////////////////////////////////////
void
StdoutTestListener::
addCaseWarning(const TestCaseInfoReader* testcase, const Warning& warning)
{
   if(level > 1) return;

   reportCaseMessage
      ( testcase
      , warn
      , ST_WARNING
      , warning.getFileName()
      , warning.getLineOfFile()
      , warning.what());
}


///////////////////////////////////////////////////////////
void
StdoutTestListener::
addCaseInfo(const TestCaseInfoReader* testcase, const Info& msg)
{
   if(level > 0) return;

   reportCaseMessage
      ( testcase
      , debug
      , ST_INFO
      , msg.getFileName()
      , msg.getLineOfFile()
      , msg.what());
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
startTestCase(const TestCaseInfoReader* testcase)
{
   if(newTags)
   {
      showTagsSpec();
      newTags = false;
   }

   if(newSuite)
   {
      showSuiteName(testcase);
      newSuite = false;
   }

   if(newFixture)
   {
     showFixtureName(testcase);
     newFixture = false;
   }

   if(!verbose) return;

   std::cout << succ << getTitle(ST_RUN) << normal
             << info << TestCaseInfo(this, testcase) << normal
             << std::endl;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
addTestResult
   ( std::vector<TestCaseResult>& set
   , const TestCaseInfoReader* testcase
   , StateTitle title )
{
   if(!verbose) return;

   set.push_back(TestCaseResult(testcase, title));
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
endTestCase
   ( const TestCaseInfoReader* testcase
   , unsigned int secs
   , unsigned int usecs)
{
   unsigned int result = \
      caseBookKeeper->getTestCaseResult(testcase);

   switch (result) 
   {
      case TestCaseResultReporter::TR_SUCCESS:
         reportCaseSuccess(testcase, secs, usecs);
         break;
      case TestCaseResultReporter::TR_FAILED:
         addTestResult(failedTests, testcase, ST_FAILED);
         break;
      case TestCaseResultReporter::TR_ERROR:
         addTestResult(failedTests, testcase, ST_ERROR);
         break;
      case TestCaseResultReporter::TR_CRASHED:   
         addTestResult(failedTests, testcase, ST_CRASHED);
         break;
      case TestCaseResultReporter::TR_SKIPPED:
         addTestResult(skippedTests, testcase, ST_SKIPPED);
         break;
      case TestCaseResultReporter::TR_UNKNOWN:
         throw Error(TESTNGPP_INTERNAL_ERROR(3001));
         break;
   }  
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
startTestFixture(TestFixtureInfoReader* fixture)
{
    newFixture = true;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
showFixtureName(const TestCaseInfoReader* testcase)
{
   if(!showFixture) return;
   
   if(!verbose && isSuccess) std::cout << std::endl;

   std::cout << std::endl;
   std::cout << info << "(" << testcase->getNameOfFixture() << ")" << normal;
   std::cout << std::endl;

   isSuccess = false;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
endTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
addFixtureError(TestFixtureInfoReader *fixture, const std::string &msg)
{
    std::ostringstream oss;
    oss << msg << " in file (" << fixture->getFileName() << ") fixture (" << fixture->getName() << ").";
    addError(oss.str());
}

///////////////////////////////////////////////////////////
void 
StdoutTestListener::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&)
{
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
startTestSuite(TestSuiteInfoReader* suite)
{
   newSuite = true;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
showSuiteName(const TestCaseInfoReader* testcase)
{
   if(!showSuite) return;
   
   std::cout << std::endl;
   std::cout
      << info 
      << formatTitle("SUITE: " + testcase->getNameOfSuite(), '-', maxLenOfLine)
      << normal
      << std::endl;

   isSuccess = false;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
endTestSuite(TestSuiteInfoReader*)
{
}

///////////////////////////////////////////////////////////
void 
StdoutTestListener::
addSuiteError(TestSuiteInfoReader*, const std::string&)
{
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
startTagsFiltering(const TagsFilterRule* filter)
{
   tags = filter->toString();
   newTags = true;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
showTagsSpec()
{
   if(!showTags) return;

   std::cout << std::endl;
   std::cout
      << info 
      << formatTitle("TAGS: {" + tags + "}",'=', maxLenOfLine)
      << normal 
      << std::endl;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
endTagsFiltering(const TagsFilterRule*)
{
}

///////////////////////////////////////////////////////////
void 
StdoutTestListener::
startTest()
{
   std::cout << std::endl;
}

///////////////////////////////////////////////////////////
template <typename State>
void
StdoutTestListener::     
reportNumber
   ( const std::string& title
   , const State& state
   , unsigned int number)
{
   if(number > 0)
   {
      std::cout 
          << " " << title << ": " 
          << state << number << normal;
   }
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::     
reportCasesResult()
{
   if(bookKeeper->getNumberOfUnsuccessfulTestCases() > 0)
   {
      unsigned int successCases = bookKeeper->getNumberOfSuccessfulTestCases();
      unsigned int rate = int(successCases*100/bookKeeper->getNumberOfTestCases()); 
      
      std::cout << std::endl;
      reportNumber("success", succ, bookKeeper->getNumberOfSuccessfulTestCases());
      reportNumber("failed",  fail, bookKeeper->getNumberOfFailedTestCases());
      reportNumber("errors",  fail, bookKeeper->getNumberOfErrorTestCases());
      reportNumber("crashed", fail, bookKeeper->getNumberOfCrashedTestCases());
      reportNumber("skipped", warn, bookKeeper->getNumberOfSkippedTestCases());
      std::cout << std::endl; 
      std::cout << " success rate: " << fail << rate << '%' << normal;
      std::cout << std::endl;
   }
   
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::     
reportSuitesResult()
{
   if(bookKeeper->getNumberOfUnloadableSuites() == 0)
   {
      return;
   }
     
   unsigned int totalSuites = 
      bookKeeper->getNumberOfLoadedSuites() +
      bookKeeper->getNumberOfUnloadableSuites();
     
   unsigned int rate = 
      (unsigned int)(100*bookKeeper->getNumberOfLoadedSuites()/totalSuites);
     
   std::cout 
      << " loaded suites: " 
      << succ 
      << bookKeeper->getNumberOfLoadedSuites()
      << normal
      << " unloadable suites: " 
      << fail
      << bookKeeper->getNumberOfUnloadableSuites()
      << normal
      << std::endl
      << " load success rate: " 
      << fail
      << rate << "%"
      << normal
      << std::endl;     
}

void
StdoutTestListener::     
reportFixturesResult()
{
   if(bookKeeper->getNumberOfErrorFixtures() == 0)
   {
      return;
   }

   std::cout 
      << " error fixtures: " 
      << fail
      << bookKeeper->getNumberOfErrorFixtures()
      << normal
      << std::endl;   
}

     
void
StdoutTestListener::
reportAllUnsuccessfulTests() const
{
   if(!verbose) return;

   std::vector<TestCaseResult>::const_iterator i = \
     failedTests.begin();

   for(; i != failedTests.end(); i++)
   {
      std::cout
         << fail << (*i).toString()
         << normal << std::endl;
   }

   for(i = skippedTests.begin(); i != skippedTests.end(); i++)
   {
      std::cout
         << warn << (*i).toString()
         << normal << std::endl;
   }
}
///////////////////////////////////////////////////////////
void
StdoutTestListener::
endTest(unsigned int secs, unsigned int usecs)
{
   if(bookKeeper->getNumberOfTestCases() == 0)
   {
      std::cout << fail << "no test to run!" << normal;
   }
   
   std::cout 
      << std::endl << std::endl
      << info 
      << formatTitle("RESULT", '=', maxLenOfLine)
      << normal 
      << std::endl;
     
   reportAllUnsuccessfulTests();

   if( ( bookKeeper->getNumberOfUnloadableSuites() 
       + bookKeeper->getNumberOfUnsuccessfulTestCases()
       + bookKeeper->getNumberOfErrorFixtures()) == 0)
   {
      std::cout
         << succ
         << getTitle(ST_SUCCESS)
         << bookKeeper->getNumberOfTestCases()
         << normal
         << " cases from "
         << succ
         << bookKeeper->getNumberOfLoadedSuites()
         << normal
         << " suites ran successfully."
         << std::endl;
   }
     
   reportSuitesResult();

   reportFixturesResult();

   reportCasesResult();

   std::cout
      << std::endl 
      << info << "(" << secs << "s " << usecs << "us)" << normal;
   std::cout << std::endl;
}

///////////////////////////////////////////////////////////
void
StdoutTestListener::
addError(const std::string& err)
{
   std::cout << fail << getTitle(ST_ERROR)
             << info << "runner: " 
             << normal << err 
             << std::endl;
}

///////////////////////////////////////////////////////////
TESTNGPP_NS_END

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
USING_TESTNGPP_NS

#define LISTENER(name) testngppstdoutlistener_##name

///////////////////////////////////////////////////////////
extern "C" DLL_EXPORT
TestListener*
LISTENER(create_instance)
     ( TestResultReporter* resultReporter
     , TestSuiteResultReporter* suiteReporter
     , TestCaseResultReporter* caseResultReporter
     , int argc
     , char** argv)
{
   OptionList options;
   
   options.parse(argc, argv, "cvsftl:");

   unsigned int level = options.getSingleUnsignedOption("l", 0);
   if(level > 3) level = 3;
   
   return new StdoutTestListener
         ( options.hasOption("c")
         , options.hasOption("s") || options.hasOption("f") 
         , options.hasOption("f")
         , options.hasOption("t")
         , options.hasOption("v")
         , level
         , resultReporter
         , suiteReporter
         , caseResultReporter);
}

///////////////////////////////////////////////////////////
extern "C" DLL_EXPORT
void
LISTENER(destroy_instance)(TestListener* instance)
{
   delete instance;
}

///////////////////////////////////////////////////////////
