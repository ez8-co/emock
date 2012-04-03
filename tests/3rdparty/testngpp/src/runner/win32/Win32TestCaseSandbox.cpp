
#include <testngpp/internal/Error.h>
#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/comm/Win32PipeReadableChannel.h>

#include <testngpp/internal/TestCase.h>

#include <testngpp/runner/EOFError.h>
#include <testngpp/runner/TestCaseRunner.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>
#include <testngpp/listener/TestCaseResultCollector.h>

#include <testngpp/win32/Win32ThrowLastError.h>
#include <testngpp/win32/Win32Sandbox.h>
#include <testngpp/win32/Win32TestCaseSandbox.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct Win32TestCaseSandboxImpl
{
   Win32TestCaseSandboxImpl()
     : testcase(0), sandbox(0), decoder(0), finished(false)
   {}

   HANDLE getSandboxId() const
   { return sandbox->getSandboxId(); }
 
   HANDLE getChannelId() const
   {
     return sandbox->getChannelId();
   }

   HANDLE getEventId() const
   {
      return sandbox->getEventId();
   }
   
   void handle(bool) TESTNGPP_THROW(Error);

   void decode() TESTNGPP_THROW(Error);
   void doDecode() TESTNGPP_THROW(Error, EOFError);

   void tryToDecodeOnDead() TESTNGPP_THROW(Error);

   void handleDeadSandbox();

   void die()
   {
	  if(!finished)
      {
         decoder->flush(true);
      }

      sandbox->die();

      finished = true;
   }

   ~Win32TestCaseSandboxImpl()
   {
      if(sandbox != 0)
         delete sandbox;

      if(decoder != 0)
         delete decoder;
   }

   bool hasSucceeded() const
   { return !decoder->hasError(); }

   const TestCase* testcase; // X
   Win32Sandbox* sandbox; // Y
   TestCaseSandboxResultDecoder* decoder; // Y
   bool finished;
};

////////////////////////////////////////////////////////
void Win32TestCaseSandboxImpl::
doDecode() TESTNGPP_THROW(Error, EOFError)
{
   __TESTNGPP_TRY
   {
      if(decoder->decode() && !finished)
      {
         finished = true;
         decoder->flush(false);
		 sandbox->die();
      }
   }
   __TESTNGPP_CATCH_ALL
   {
      die();
	  throw;
   }
   __TESTNGPP_END_TRY
}

////////////////////////////////////////////////////////
void Win32TestCaseSandboxImpl::
decode() TESTNGPP_THROW(Error)
{
	__TESTNGPP_TRY
	{
		doDecode();
	}__TESTNGPP_CATCH(EOFError&)
	__TESTNGPP_END_TRY
}

void Win32TestCaseSandboxImpl::
tryToDecodeOnDead() TESTNGPP_THROW(Error)
{
   DWORD result = 
      ::WaitForSingleObject
	     ( getEventId()
		 , 1);
   switch(result)
   {
   case WAIT_OBJECT_0:
	   decode();
	   break;
   case WAIT_ABANDONED:
   case WAIT_TIMEOUT:
       die();
	   break;
   case WAIT_FAILED:
	   die();
	   throwLastError();
   }
}
void Win32TestCaseSandboxImpl::
handleDeadSandbox() TESTNGPP_THROW(Error)
{
	while(!sandbox->isDead())
	{
		tryToDecodeOnDead();
	}
}
////////////////////////////////////////////////////////
void Win32TestCaseSandboxImpl::
handle(bool isDead) TESTNGPP_THROW(Error)
{
   if(sandbox->isDead())
   {
      return;
   }

   if(isDead)
   {
	   handleDeadSandbox();
	   return;
   }

   decode();
}

////////////////////////////////////////////////////////
Win32TestCaseSandbox::Win32TestCaseSandbox()
   : This(new Win32TestCaseSandboxImpl())
{}

////////////////////////////////////////////////////////
Win32TestCaseSandbox::
~Win32TestCaseSandbox()
{
	delete This;
}

////////////////////////////////////////////////////////
HANDLE 
Win32TestCaseSandbox::
getEventId() const
{
   return This->getEventId();
}

////////////////////////////////////////////////////////
HANDLE 
Win32TestCaseSandbox::
getSandboxId() const
{
   return This->getSandboxId();
}

////////////////////////////////////////////////////////
bool 
Win32TestCaseSandbox::
hasSucceeded() const
{
   return This->hasSucceeded();
}

const TestCase*
Win32TestCaseSandbox::
getTestCase() const
{
   return This->testcase;
}

////////////////////////////////////////////////////////
void
Win32TestCaseSandbox::
handle(bool isDead) TESTNGPP_THROW(EOFError, Error)
{
   This->handle(isDead);
}

////////////////////////////////////////////////////////
bool
Win32TestCaseSandbox::
isDead() const
{
   return This->sandbox->isDead();
}
////////////////////////////////////////////////////////
void
Win32TestCaseSandbox::
cleanup()
{
   This->sandbox->cleanup();
}
////////////////////////////////////////////////////////
Win32TestCaseSandbox*
Win32TestCaseSandbox::
createInstance
       ( const std::string& suitePath
	   , const TestCase* testcase
       , TestCaseRunner* runner
       , TestCaseResultCollector* collector
       , bool shouldReport)
{
   Win32Sandbox* sandbox = Win32Sandbox::createInstance(suitePath, testcase);
   
   Win32TestCaseSandbox* tcSandbox = new Win32TestCaseSandbox();

   tcSandbox->This->decoder = \
         new TestCaseSandboxResultDecoder
            ( new Win32PipeReadableChannel(sandbox->getChannelId())
            , testcase
            , collector
            , shouldReport);

   tcSandbox->This->testcase = testcase;
   tcSandbox->This->sandbox = sandbox;

   return tcSandbox;
}

TESTNGPP_NS_END

