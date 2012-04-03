
#include <sstream>
#include <vector>

#include <errno.h>

#include <testngpp/utils/InternalError.h>
#include <testngpp/utils/StupidTimer.h>

#include <testngpp/internal/AssertionFailure.h>
#include <testngpp/internal/Warning.h>
#include <testngpp/internal/Info.h>

#include <testngpp/runner/TestCaseSandboxResultReporter.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>

#include <testngpp/comm/WrittableChannel.h>
#include <testngpp/comm/ReadableChannel.h>

TESTNGPP_NS_START

namespace
{
   struct InfoContainer
   {
      void flush( const TestCaseInfoReader* testcase
                , TestCaseResultCollector* collector)
      {
        unsigned int indexOfInfos  = 0;
        unsigned int indexOfWarns  = 0;
		unsigned int indexOfFails  = 0;
		unsigned int indexOfErrors = 0;
 
        for(unsigned int i=0; i<types.size(); i++)
        {
			switch(types[i])
			{
			case 0: collector->addCaseInfo(testcase, infos[indexOfInfos++]); break;
			case 1: collector->addCaseWarning(testcase, warns[indexOfWarns++]); break;
			case 2: collector->addCaseFailure(testcase, failures[indexOfFails++]); break;
			case 3: collector->addCaseError(testcase, errors[indexOfErrors++]); break;
			}
        }

        types.clear();
        infos.clear();
        warns.clear();
      }

	  void addInfo(const Info& info)
      {
         types.push_back(0);
         infos.push_back(info);
      }

      void addWarning(const Warning& warn)
      {
         types.push_back(1);
         warns.push_back(warn);
      }

	  void addFailure(const AssertionFailure& failure)
	  {
		  types.push_back(2);
		  failures.push_back(failure);
	  }

	  void addError(const std::string& error)
	  {
		  types.push_back(3);
		  errors.push_back(error);
	  }

      std::vector<unsigned char> types;

      std::vector<Info> infos;
      std::vector<Warning> warns;
	  std::vector<AssertionFailure> failures;
	  std::vector<std::string> errors;
   };

}

struct TestCaseSandboxResultDecoderImpl
{
	void addCaseError(const std::string& msg);
	void addCaseFailure(const AssertionFailure& failure);
	void addCaseInfo(const Info& info);
	void addCaseWarning(const Warning& warning);

   AssertionFailure readAssertionFailure();
   Warning readWarning();
   Info readInfo();
   timeval readTime();

   void handleInfo();
   void handleWarning();
   void handleAssertionFailure();
   void handleError();
   void handleInternalError();
   void handleStartCase();
   void handleEndCase();

   void flushRegularEvents();
   void flushInfoEvents();
   void flushEndEvent();

   bool decode();
   void flush(bool crashed);

   TestCaseSandboxResultDecoderImpl(ReadableChannel* ch
             , const TestCaseInfoReader* tc
             , TestCaseResultCollector* rc
             , bool report)
      : channel(ch), testcase(tc), collector(rc)
      , startReceived(false), endReceived(false)
      , errorReceived(false), failureReceived(false)
      , infoReceived(false)
      , crashInformed(false), reportSuccess(report)
   {
      endTime.tv_sec  = 0;
      endTime.tv_usec = 0;
   }

   ~TestCaseSandboxResultDecoderImpl()
   {
      if(channel != 0)
      { delete channel; }
   }

   bool hasError() const
   { return errorReceived || failureReceived || crashInformed; }

   bool couldRecvEvents() const
   { return (startReceived && !endReceived && !crashInformed); }

   ReadableChannel* channel; // Y

   const TestCaseInfoReader* testcase; // X
   TestCaseResultCollector* collector; // X
  

   StupidTimer timer;
   timeval endTime;

   InfoContainer infos;
   
   bool startReceived;
   bool endReceived;
   bool errorReceived;
   bool failureReceived;
   bool infoReceived;
   bool crashInformed;
   bool reportSuccess;
};

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
addCaseError(const std::string& msg)
{
   if(!couldRecvEvents())
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1001));
   }

   infos.addError(msg);

   errorReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
addCaseFailure(const AssertionFailure& failure)
{
   if(!couldRecvEvents())
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1002));
   }

   infos.addFailure(failure);

   failureReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
addCaseInfo(const Info& info)
{
   if(!couldRecvEvents())
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1006));
   }

   infos.addInfo(info);
  
   infoReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
addCaseWarning(const Warning& warning)
{
   if(!couldRecvEvents())
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1007));
   }

   infos.addWarning(warning);
  
   infoReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
flushInfoEvents()
{
   infos.flush(testcase, collector);
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
flushEndEvent()
{
   if(endReceived)
   {
      collector->endTestCase(testcase, endTime.tv_sec, endTime.tv_usec);
   }
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
flushRegularEvents()
{
   if(!startReceived)
   {
      return;
   }

   if(!(reportSuccess || hasError()))
   { 
      return;
   }

   collector->startTestCase(testcase);

   flushInfoEvents();

   flushEndEvent();
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
flush(bool crashed)
{
   if(crashInformed)
   {
      return;
   }

   flushRegularEvents();

   if(crashed && !endReceived)
   {
	  if(!startReceived)
	  {
		collector->startTestCase(testcase);
	  }
      collector->addCaseCrash(testcase);
      timeval tv = timer.stop();
      collector->endTestCase(testcase, tv.tv_sec, tv.tv_usec);
      crashInformed = true;
   }
}

/////////////////////////////////////////////////////////////////////////
namespace
{
   const unsigned char startCmd   = 1;
   const unsigned char endCmd     = 2;
   const unsigned char errorCmd   = 3;
   const unsigned char failureCmd = 4;
   const unsigned char infoCmd    = 5;
   const unsigned char warningCmd = 6;
}

/////////////////////////////////////////////////////////////
timeval
TestCaseSandboxResultDecoderImpl::
readTime()
{
   timeval tv;

   tv.tv_sec  = channel->readInt();
   tv.tv_usec = channel->readInt();

   return tv;
}

/////////////////////////////////////////////////////////////
AssertionFailure
TestCaseSandboxResultDecoderImpl::
readAssertionFailure()
{
   std::string file = channel->readString();
   int line = channel->readInt();
   std::string reason = channel->readString();
   return AssertionFailure(file, line, reason);
}

/////////////////////////////////////////////////////////////
Info
TestCaseSandboxResultDecoderImpl::
readInfo()
{
   std::string file = channel->readString();
   int line = channel->readInt();
   std::string reason = channel->readString();
   return Info(file, line, reason);
}

/////////////////////////////////////////////////////////////
Warning
TestCaseSandboxResultDecoderImpl::
readWarning()
{
   std::string file = channel->readString();
   int line = channel->readInt();
   std::string reason = channel->readString();
   return Warning(file, line, reason);
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleAssertionFailure()
{
   addCaseFailure(readAssertionFailure());
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleInfo()
{
   addCaseInfo(readInfo());
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleWarning()
{
   addCaseWarning(readWarning());
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleError()
{
   addCaseError(channel->readString());
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleInternalError()
{
   const char * err = TESTNGPP_INTERNAL_ERROR(1003);
   addCaseError(err);
   throw Error(err);
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleStartCase()
{
   if( startReceived   ||
       endReceived     || 
       errorReceived   ||
       failureReceived || 
       crashInformed)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1004));
   }

   startReceived = true;
   timer.start();
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::
handleEndCase()
{
   if( endReceived   ||
      !startReceived ||
       crashInformed)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1005));
   }

   endTime = readTime();

   endReceived = true;
}
/////////////////////////////////////////////////////////////////////////
bool TestCaseSandboxResultDecoderImpl::decode()
{
   switch(channel->readByte())
   {
   case startCmd:
      handleStartCase(); break;
   case endCmd:
      handleEndCase();
      return true;
   case errorCmd:
      handleError(); break;
   case failureCmd:
      handleAssertionFailure(); break;
   case infoCmd:
      handleInfo(); break;
   case warningCmd:
      handleWarning(); break;
   default:
      handleInternalError();
   }
   return false;
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultDecoder::
TestCaseSandboxResultDecoder
      ( ReadableChannel* channel
      , const TestCaseInfoReader* testcase
      , TestCaseResultCollector* collector
      , bool shouldReport)
      : This(new TestCaseSandboxResultDecoderImpl
          (channel, testcase, collector, shouldReport))
{
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultDecoder::~TestCaseSandboxResultDecoder()
{
   delete This;
}

/////////////////////////////////////////////////////////////////////////
bool TestCaseSandboxResultDecoder::decode()
{
   return This->decode();
}

/////////////////////////////////////////////////////////////////////////
bool TestCaseSandboxResultDecoder::hasError() const
{
   return This->hasError();
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultDecoder::flush(bool crashed)
{
   This->flush(crashed);
}

/////////////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

