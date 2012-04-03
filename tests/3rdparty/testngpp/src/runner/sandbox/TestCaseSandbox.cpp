
#include <sys/types.h>
#include <sys/socket.h>

#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/comm/PipeReadableChannel.h>

#include <testngpp/internal/Error.h>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TestCase.h>

#include <testngpp/listener/TestCaseResultCollector.h>

#include <testngpp/runner/EOFError.h>
#include <testngpp/runner/TestCaseRunner.h>
#include <testngpp/runner/Sandbox.h>
#include <testngpp/runner/EnvironmentCleaner.h>
#include <testngpp/runner/TestCaseSandboxHandler.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>
#include <testngpp/runner/TestCaseSandbox.h>



TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct TestCaseSandboxImpl
{
   TestCaseSandboxImpl()
     : testcase(0), sandbox(0), decoder(0), finished(false)
   {}

   SandboxId getSandboxId() const
   { return sandbox->getSandboxId(); }
 
   ChannelId getChannelId() const
   {
     return sandbox->getChannelId();
   }

   void handle() TESTNGPP_THROW(EOFError, Error);

   ~TestCaseSandboxImpl()
   {
      if(sandbox != 0)
         delete sandbox;

      if(decoder != 0)
         delete decoder;
   }

   bool hasSucceeded() const
   { return !decoder->hasError(); }

   const TestCase* testcase; // X
   Sandbox* sandbox; // Y
   TestCaseSandboxResultDecoder* decoder; // Y
   bool finished;
};

////////////////////////////////////////////////////////
void TestCaseSandboxImpl::handle() TESTNGPP_THROW(EOFError, Error)
{
   if(sandbox->isDead())
   {
      return;
   }

   __TESTNGPP_TRY
   {
	   bool result = decoder->decode();
      if(result && !finished)
      {
         finished = true;
         decoder->flush(false);
      }
   }
   __TESTNGPP_CATCH(EOFError&)
   {
      if(!finished)
      {
         decoder->flush(true);
      }

      sandbox->die();

      finished = true;
   }
   __TESTNGPP_END_TRY
}

////////////////////////////////////////////////////////
TestCaseSandbox::TestCaseSandbox()
   : This(new TestCaseSandboxImpl())
{}

////////////////////////////////////////////////////////
TestCaseSandbox::~TestCaseSandbox()
{
	delete This;
}

////////////////////////////////////////////////////////
ChannelId TestCaseSandbox::getChannelId() const
{
   return This->getChannelId();
}

////////////////////////////////////////////////////////
bool TestCaseSandbox::hasSucceeded() const
{
   return This->hasSucceeded();
}

const TestCase*
TestCaseSandbox::getTestCase() const
{
   return This->testcase;
}

////////////////////////////////////////////////////////
void
TestCaseSandbox::handle() TESTNGPP_THROW(EOFError, Error)
{
   This->handle();
}

////////////////////////////////////////////////////////
bool
TestCaseSandbox::isDead() const
{
   return This->sandbox->isDead();
}
////////////////////////////////////////////////////////
void
TestCaseSandbox::cleanup()
{
   This->sandbox->cleanup();
}
////////////////////////////////////////////////////////
TestCaseSandbox*
TestCaseSandbox::
createInstance
       ( EnvironmentCleaner* cleaner
       , const TestCase* testcase
       , TestCaseRunner* runner
       , TestCaseResultCollector* collector
       , bool shouldReport)
{
   TestCaseSandboxHandler handler(testcase, runner);
   Sandbox* sandbox = Sandbox::createInstance(cleaner, &handler);
   if(sandbox == 0)
   {
      throw Error("system error: cannot create object");
   }

   TestCaseSandbox* tcSandbox = new TestCaseSandbox();

   tcSandbox->This->decoder = \
         new TestCaseSandboxResultDecoder
            ( new PipeReadableChannel(sandbox->getChannelId())
            , testcase
            , collector
            , shouldReport);

   tcSandbox->This->testcase = testcase;
   tcSandbox->This->sandbox = sandbox;

   return tcSandbox;
}

TESTNGPP_NS_END

