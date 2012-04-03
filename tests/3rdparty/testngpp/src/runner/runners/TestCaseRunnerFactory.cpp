
#include <testngpp/runner/SimpleTestCaseRunner.h>
#include <testngpp/runner/TestCaseRunnerFactory.h>

TESTNGPP_NS_START
////////////////////////////////////////////////////////
namespace
{
   unsigned int ref = 0;

   TestCaseRunner* caseRunner = 0;
}

TestCaseRunner*
TestCaseRunnerFactory::createInstance()
{
   if(caseRunner == 0)
   {
      caseRunner = new SimpleTestCaseRunner();
      ref = 1;
   }
   else
   {
      ref++;
   }

   return caseRunner;
}

void 
TestCaseRunnerFactory::releaseInstance(TestCaseRunner* runner)
{
   if(ref == 0)
   {
      return;
   }

   if(--ref == 0)
   {
      delete caseRunner;
      caseRunner = 0;
   }
}

TESTNGPP_NS_END

