
#include <sstream>

#if defined(_MSC_VER)
#include <windows.h>
#endif

#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/utils/StupidTimer.h>

#include <testngpp/internal/TestCase.h>
#include <testngpp/internal/TestFixtureDesc.h>

#include <testngpp/listener/TestCaseResultCollector.h>

#include <testngpp/runner/SimpleTestCaseRunner.h>
#include <testngpp/runner/SmartTestCaseResultCollector.h>

TESTNGPP_NS_START

#if defined(_MSC_VER)
namespace {
struct HwExceptionEntry
{
	unsigned int code;
	const char* name;
};

#define HW_EXCEPTION(code) {code, #code}

static HwExceptionEntry hwExceptionTable[] =
{
	HW_EXCEPTION(STATUS_GUARD_PAGE_VIOLATION),
    HW_EXCEPTION(STATUS_ACCESS_VIOLATION),
    HW_EXCEPTION(STATUS_IN_PAGE_ERROR),
	HW_EXCEPTION(STATUS_INVALID_HANDLE),
	HW_EXCEPTION(STATUS_NO_MEMORY),
	HW_EXCEPTION(STATUS_ILLEGAL_INSTRUCTION),
	HW_EXCEPTION(STATUS_NONCONTINUABLE_EXCEPTION),
	HW_EXCEPTION(STATUS_INVALID_DISPOSITION),
	HW_EXCEPTION(STATUS_ARRAY_BOUNDS_EXCEEDED),
	HW_EXCEPTION(STATUS_FLOAT_DENORMAL_OPERAND),
	HW_EXCEPTION(STATUS_FLOAT_DIVIDE_BY_ZERO),
	HW_EXCEPTION(STATUS_FLOAT_INEXACT_RESULT),
	HW_EXCEPTION(STATUS_FLOAT_INVALID_OPERATION),
	HW_EXCEPTION(STATUS_FLOAT_OVERFLOW),
	HW_EXCEPTION(STATUS_FLOAT_STACK_CHECK),
	HW_EXCEPTION(STATUS_FLOAT_UNDERFLOW),
	HW_EXCEPTION(STATUS_INTEGER_DIVIDE_BY_ZERO),
	HW_EXCEPTION(STATUS_INTEGER_OVERFLOW),
	HW_EXCEPTION(STATUS_PRIVILEGED_INSTRUCTION),
	HW_EXCEPTION(STATUS_STACK_OVERFLOW),
	HW_EXCEPTION(STATUS_CONTROL_C_EXIT),
	HW_EXCEPTION(STATUS_FLOAT_MULTIPLE_FAULTS),
	HW_EXCEPTION(STATUS_FLOAT_MULTIPLE_TRAPS),
	HW_EXCEPTION(STATUS_REG_NAT_CONSUMPTION)
};

std::string exceptionCodeToStr(unsigned int code)
{
	for(unsigned int i=0; i<sizeof(hwExceptionTable)/sizeof(hwExceptionTable[0]); i++)
	{
		if(hwExceptionTable[i].code == code)
			return hwExceptionTable[i].name;
	}

	std::ostringstream oss;

	oss << "unknown (" << code << ")";
	return oss.str();
}
}
#endif

#define __RUN(block) try block \
   catch(AssertionFailure&) \
   { \
      hasFailure = true; \
   } \
   catch(std::exception& e) \
   { \
      collector->addCaseError(testcase, e.what()); \
      hasFailure = true; \
   } \
   catch(...) \
   { \
      collector->addCaseError(testcase, "Unknown Exception"); \
      hasFailure = true; \
   }

namespace
{
bool beginTest
      ( TestCase* testcase
      , TestCaseResultCollector* collector)
{
   bool hasFailure = false;

   __RUN({
      testcase->setUp();
      testcase->run();
   });

   return hasFailure;
}

bool endTest
      ( TestCase* testcase
      , TestCaseResultCollector* collector)
{
   bool hasFailure = false;

   __RUN({
      testcase->tearDown();
   });

   return hasFailure;
}

bool runTest
      ( TestCase* testcase
      , TestCaseResultCollector* collector)
{
   bool hasFailure = false;

   hasFailure = beginTest(testcase, collector);
   hasFailure = endTest(testcase, collector);

   return !hasFailure;
}

#if defined(_MSC_VER)
void addHardwareError
      ( TestCase* testcase
      , TestCaseResultCollector* collector    
      , int exceptionCode
      , const char *str)
{
    std::ostringstream oss;
    oss << "hardware exception " << exceptionCodeToStr(exceptionCode) << " raised "<< str;
    collector->addCaseError(testcase, oss.str());
}

bool win32TryToRunTest
      ( TestCase* testcase
      , TestCaseResultCollector* collector)
{
    bool hasFailure = false;

	__try
	{
        hasFailure = beginTest(testcase, collector);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{   
        hasFailure = true;
        addHardwareError(testcase, collector, ::GetExceptionCode(), "in setup or running test");
	}

    __try
	{
        hasFailure = endTest(testcase, collector);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{   
        hasFailure = true;
        addHardwareError(testcase, collector, ::GetExceptionCode(), "in teardown");
	}

	return !hasFailure;
}
#endif


bool doRun
   ( TestCase* testcase
   , TestCaseResultCollector* collector)
{
#if defined(_MSC_VER)
   return win32TryToRunTest(testcase, collector);
#else
   return runTest(testcase, collector);
#endif
}

}

//////////////////////////////////////////
bool SimpleTestCaseRunner::run
      ( TestCase* testcase
      , TestCaseResultCollector* collector
      , bool reportSuccess)
{
   bool success = false;

   TestCaseResultCollector* smartCollector =
         new SmartTestCaseResultCollector(collector, reportSuccess);

   testcase->setFixture();
   testcase->getFixture()->setCurrentTestCase(testcase, smartCollector);

   smartCollector->startTestCase(testcase);

   StupidTimer timer;

   __TESTNGPP_DO

   timer.start();
   success = doRun(testcase, smartCollector);

   __TESTNGPP_CLEANUP

   testcase->verifyMemChecker(); // avoid affecting the following testcase.
   timeval e = timer.stop();
   smartCollector->endTestCase(testcase, e.tv_sec, e.tv_usec);
   delete smartCollector;
   //delete testcase->getFixture(); // when test case run finish, there is a delete in tearDown, this is duplicate.

   __TESTNGPP_DONE

   return success;
}

TESTNGPP_NS_END

