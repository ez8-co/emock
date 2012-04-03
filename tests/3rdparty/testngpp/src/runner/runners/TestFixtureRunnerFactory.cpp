
#include <testngpp/runner/TestFixtureRunner.h>
#include <testngpp/runner/SimpleTestHierarchyRunner.h>
#include <testngpp/runner/TestCaseRunnerFactory.h>
#include <testngpp/runner/TestFixtureRunnerFactory.h>

#if !defined(TESTNGPP_DISABLE_SANDBOX) || !TESTNGPP_DISABLE_SANDBOX
#if defined(_MSC_VER)
#include <testngpp/win32/Win32TestHierarchySandboxRunner.h>
#else
#include <testngpp/runner/TestHierarchySandboxRunner.h>
#endif
#endif

TESTNGPP_NS_START

namespace
{

#if !defined(TESTNGPP_DISABLE_SANDBOX) || !TESTNGPP_DISABLE_SANDBOX
   TestFixtureRunner*
   createSandboxInstance(unsigned int maxConcurrent)
   {
      if(maxConcurrent == 0)
      {
         maxConcurrent = 1;
      }

      return new TestFixtureRunner( 
#if defined(_MSC_VER)
		          new Win32TestHierarchySandboxRunner(
#else
		          new TestHierarchySandboxRunner( 
#endif
                     maxConcurrent, TestCaseRunnerFactory::createInstance()));
   }
#endif

   TestFixtureRunner*
   createSimpleInstance()
   {
      return new TestFixtureRunner( \
                  new SimpleTestHierarchyRunner( \
				  TestCaseRunnerFactory::createInstance()));
   }
}


////////////////////////////////////////////////////////
TestFixtureRunner*
TestFixtureRunnerFactory::
createInstance(bool useSandbox, unsigned int maxConcurrent)
{
#if defined(TESTNGPP_DISABLE_SANDBOX) && TESTNGPP_DISABLE_SANDBOX
   return createSimpleInstance();
#else
   return useSandbox? createSandboxInstance(maxConcurrent) :
      createSimpleInstance();
#endif
}

////////////////////////////////////////////////////////
void 
TestFixtureRunnerFactory::
destroyInstance(TestFixtureRunner* instance)
{
   if(instance == 0)
   {
      return;
   }

   delete instance;

   TestCaseRunnerFactory::releaseInstance(0);
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END
