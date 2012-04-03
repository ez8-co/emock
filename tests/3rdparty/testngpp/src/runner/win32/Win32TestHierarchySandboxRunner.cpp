
#include <list>
#include <algorithm>
#include <iostream>

#include <windows.h>

#include <testngpp/internal/TestCase.h>

#include <testngpp/runner/TestCaseHierarchy.h>

#include <testngpp/runner/TestCaseRunner.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>
#include <testngpp/listener/TestFixtureResultCollector.h>
#include <testngpp/runner/TestHierarchyHandler.h>

#include <testngpp/win32/Win32ThrowLastError.h>
#include <testngpp/win32/Win32TestCaseSandbox.h>
#include <testngpp/win32/Win32TestHierarchySandboxRunner.h>

TESTNGPP_NS_START

///////////////////////////////////////////////////////
struct Win32TestHierarchySandboxRunnerImpl 
{
   typedef std::list<Win32TestCaseSandbox*> List;

	Win32TestHierarchySandboxRunnerImpl
      ( unsigned int maxCurrentProcess
      , TestCaseRunner* runner)
      : maxProcess(maxCurrentProcess)
      , caseRunner(runner)
      , index(0)
	  , handles(0)
   {}

	~Win32TestHierarchySandboxRunnerImpl()
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
   void handleEvent(unsigned int index, bool isDead, TestHierarchyHandler* handler);

   void cleanUp();

   const unsigned int maxProcess;
   TestCaseRunner* caseRunner;
   unsigned int    index;
   List sandboxes;
   HANDLE*         handles;
};

////////////////////////////////////////////////////
namespace 
{
   static void removeSandbox(Win32TestCaseSandbox* sandbox)
   {
      delete sandbox;
   }
}

////////////////////////////////////////////////////
void Win32TestHierarchySandboxRunnerImpl::cleanUp()
{
   std::for_each(sandboxes.begin(), sandboxes.end(), removeSandbox);
   sandboxes.clear();
   if(handles != 0)
   {
      delete [] handles;
   }
}

////////////////////////////////////////////////////
namespace
{
    static bool isDead(Win32TestCaseSandbox* sandbox)
    {
       return sandbox->isDead();  
    }
}

////////////////////////////////////////////////////
void Win32TestHierarchySandboxRunnerImpl::
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
void Win32TestHierarchySandboxRunnerImpl::
createSandbox
      ( TestHierarchyHandler* handler
	  , unsigned int i
      , TestFixtureResultCollector* resultCollector)
{
   TestHierarchyHandler::ValueType testcase = handler->getTestCase(i);
   Win32TestCaseSandbox* sandbox = \
         Win32TestCaseSandbox::createInstance
               ( handler->getSuitePath()
			   , testcase.first
               , caseRunner
               , resultCollector
               , testcase.second);

   sandboxes.push_back(sandbox);
}

////////////////////////////////////////////////////
void Win32TestHierarchySandboxRunnerImpl::
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
void 
Win32TestHierarchySandboxRunnerImpl::
setupListeners()
{
   if(handles != 0)
   {
      delete [] handles;
	  handles = 0;
   }
   
   if(sandboxes.size() == 0)
   {
      return;
   }
   
   handles = new HANDLE[sandboxes.size()*2];

   int i = 0;
   List::iterator iter = sandboxes.begin();
   for(; iter != sandboxes.end(); iter++)
   {
	  handles[i++] = (*iter)->getEventId();
      handles[i++] = (*iter)->getSandboxId();
   }
}

///////////////////////////////////////////////////////
namespace
{
   static void handleSandboxEvent(Win32TestCaseSandbox* sandbox, bool isDead)
   {
      sandbox->handle(isDead);
   }
}
///////////////////////////////////////////////////////
void Win32TestHierarchySandboxRunnerImpl::
handleEvent(unsigned int index, bool isDead, TestHierarchyHandler* handler)
{
   List::iterator i = sandboxes.begin();
   for(; i != sandboxes.end(); i++)
   {
      if((*i)->getSandboxId() == handles[index*2+1])
      {
         handleSandboxEvent(*i, isDead);
		 break;
      }
   }

   cleanUpDeadSandboxes(handler);
}

///////////////////////////////////////////////////////
void Win32TestHierarchySandboxRunnerImpl::
process(TestHierarchyHandler* handler)
{
   setupListeners();

   DWORD result = 
      ::WaitForMultipleObjects
	     ( sandboxes.size()*2
		 , handles
		 , FALSE
		 , INFINITE);
   if(result == WAIT_FAILED)
   {
      throwLastError();
   }
   
   if(WAIT_OBJECT_0 > result || result >= WAIT_OBJECT_0 + sandboxes.size() * 2)
   {
      throw Error("Invalid WaitForMultipleObjects result");
   }   

   handleEvent
	   ( (result-WAIT_OBJECT_0)/2
	   , (result-WAIT_OBJECT_0)%2>0 ? true : false
	   , handler);
}

///////////////////////////////////////////////////////
void
Win32TestHierarchySandboxRunnerImpl::
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
Win32TestHierarchySandboxRunner::
Win32TestHierarchySandboxRunner
   ( unsigned int maxCurrentProcess
   , TestCaseRunner* caseRunner)
   : This(new Win32TestHierarchySandboxRunnerImpl
      ( maxCurrentProcess
	  , caseRunner))
{
}

///////////////////////////////////////////////////////
Win32TestHierarchySandboxRunner::
~Win32TestHierarchySandboxRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
void
Win32TestHierarchySandboxRunner::
run
   ( TestHierarchyHandler* handler
   , TestFixtureResultCollector* resultCollector)
{
   This->run(handler, resultCollector);
}

///////////////////////////////////////////////////////

TESTNGPP_NS_END

