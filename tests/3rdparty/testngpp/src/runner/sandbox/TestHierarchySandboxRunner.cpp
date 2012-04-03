
// for select
#include <sys/select.h>
#include <errno.h>
#include <list>
#include <algorithm>
#include <string.h>

#include <testngpp/internal/TestCase.h>

#include <testngpp/listener/TestFixtureResultCollector.h>

#include <testngpp/runner/TestCaseHierarchy.h>
#include <testngpp/runner/TestHierarchySandboxRunner.h>
#include <testngpp/runner/TestCaseRunner.h>
#include <testngpp/runner/TestCaseSandboxResultReporter.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>
#include <testngpp/runner/TestCaseSandbox.h>
#include <testngpp/runner/EnvironmentCleaner.h>
#include <testngpp/runner/TestCaseContainer.h>
#include <testngpp/runner/TestHierarchyHandler.h>


TESTNGPP_NS_START

///////////////////////////////////////////////////////
struct TestHierarchySandboxRunnerImpl 
   : public EnvironmentCleaner
{
   typedef std::list<TestCaseSandbox*> List;

	TestHierarchySandboxRunnerImpl
      ( unsigned int maxCurrentProcess
      , TestCaseRunner* runner)
      : maxProcess(maxCurrentProcess)
      , caseRunner(runner)
      , index(0)
   {}

	~TestHierarchySandboxRunnerImpl()
   {
      cleanUp();
   }

	void run(TestHierarchyHandler* hierarchy
      , TestFixtureResultCollector* resultCollector);

   void setupListeners();
   void createSandbox( TestHierarchyHandler* handler, unsigned int i
             , TestFixtureResultCollector* resultCollector);


   void createSandboxes(TestHierarchyHandler* handler 
             , TestFixtureResultCollector* resultCollector);

   void cleanUpDeadSandboxes(TestHierarchyHandler*);

   void process(TestHierarchyHandler* hierarchy);
   void handleEvent(int nfds, TestHierarchyHandler* hierarchy);

   void cleanUp();

   const unsigned int maxProcess;
   TestCaseRunner* caseRunner;
   unsigned int    index;
   fd_set          fds;
   int             maxfd;
   List sandboxes;
};

////////////////////////////////////////////////////
namespace 
{
   static void removeSandbox(TestCaseSandbox* sandbox)
   {
      delete sandbox;
   }
}

////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::cleanUp()
{
   std::for_each(sandboxes.begin(), sandboxes.end(), removeSandbox);
   sandboxes.clear();
}

////////////////////////////////////////////////////
namespace
{
    static bool isDead(TestCaseSandbox* sandbox)
    {
       return sandbox->isDead();  
    }
}

////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::
cleanUpDeadSandboxes(TestHierarchyHandler* handler)
{
   while(1)
   {
      List::iterator i = std::find_if(sandboxes.begin(), sandboxes.end(), isDead);
      if(i == sandboxes.end())
      {
         break;
      }

      handler->testDone((*i)->getTestCase(), (*i)->hasSucceeded());

      (*i)->cleanup();
      delete *i;
      sandboxes.erase(i);
   }
}

////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::
createSandbox( TestHierarchyHandler* handler, unsigned int i
             , TestFixtureResultCollector* resultCollector)
{
   TestHierarchyHandler::ValueType testcase = handler->getTestCase(i);
   TestCaseSandbox* sandbox = \
         TestCaseSandbox::createInstance
               ( this
               , testcase.first
               , caseRunner
               , resultCollector
               , testcase.second);

   sandboxes.push_back(sandbox);
}

////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::
createSandboxes
      ( TestHierarchyHandler* handler
      , TestFixtureResultCollector* resultCollector)
{
   unsigned int numberOfTestCases = handler->numberOfTestCasesInSched();
   unsigned int i = index;
   for(; i < numberOfTestCases && sandboxes.size() < maxProcess; i++)
   {
      createSandbox(handler, i, resultCollector);
   }

   index = i;
}


/////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::setupListeners()
{
   FD_ZERO(&fds);
   maxfd = 0;

   List::iterator i = sandboxes.begin();
   for(; i != sandboxes.end(); i++)
   {
      FD_SET((*i)->getChannelId(), &fds);
      maxfd = maxfd < (*i)->getChannelId() ? (*i)->getChannelId() : maxfd;
   }
}

///////////////////////////////////////////////////////
namespace
{
   static void handleSandboxEvent(TestCaseSandbox* sandbox)
   {
      sandbox->handle();
   }
}
///////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::
handleEvent(int nfds, TestHierarchyHandler* handler)
{
   List::iterator i = sandboxes.begin();
   for(; i != sandboxes.end(); i++)
   {
      if(FD_ISSET((*i)->getChannelId(), &fds))
      {
         handleSandboxEvent(*i);
         if(--nfds <= 0)
         {
            break;
         }
      }
   }

   cleanUpDeadSandboxes(handler);
}

///////////////////////////////////////////////////////
void TestHierarchySandboxRunnerImpl::
process(TestHierarchyHandler* handler)
{
   setupListeners();

   int nfds = 0;
   do{
      nfds = ::select(maxfd + 1, &fds, 0, 0, 0);
   }while(nfds == 0 || (nfds < 0 && errno == EAGAIN));

   if(nfds < 0)
   {
      throw Error(strerror(errno));
   }

   handleEvent(nfds, handler);
}

///////////////////////////////////////////////////////
void
TestHierarchySandboxRunnerImpl::
run( TestHierarchyHandler* handler
   , TestFixtureResultCollector* resultCollector)
{
   index = 0;

   while(1)
   {
      createSandboxes(handler, resultCollector);
      if(sandboxes.size() == 0)
      {
         break;
      }

      process(handler);
   }
}

///////////////////////////////////////////////////////
TestHierarchySandboxRunner::TestHierarchySandboxRunner(
     unsigned int maxCurrentProcess
   , TestCaseRunner* caseRunner)
   : This(new TestHierarchySandboxRunnerImpl(maxCurrentProcess, caseRunner))
{
}

///////////////////////////////////////////////////////
TestHierarchySandboxRunner::~TestHierarchySandboxRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
void
TestHierarchySandboxRunner::run(TestHierarchyHandler* handler
      , TestFixtureResultCollector* resultCollector)
{
   This->run(handler, resultCollector);
}

///////////////////////////////////////////////////////

TESTNGPP_NS_END

