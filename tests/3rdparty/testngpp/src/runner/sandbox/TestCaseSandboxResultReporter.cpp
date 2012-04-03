
#include <sstream>
#include <errno.h>

#include <testngpp/internal/AssertionFailure.h>

#include <testngpp/runner/TestCaseSandboxResultReporter.h>

#include <testngpp/comm/WrittableChannel.h>
#include <testngpp/comm/ReadableChannel.h>

TESTNGPP_NS_START

struct TestCaseSandboxResultReporterImpl
{
   TestCaseSandboxResultReporterImpl(WrittableChannel* c)
		: channel(c)
   {}

   ~TestCaseSandboxResultReporterImpl()
   { delete channel; }

	void addCaseError(const TestCaseInfoReader* testCase, const std::string& msg);
	void addCaseFailure(const TestCaseInfoReader* testCase, const AssertionFailure& failure);
	void addCaseInfo(const TestCaseInfoReader* testCase, const Info& info);
	void addCaseWarning(const TestCaseInfoReader* testCase, const Warning& warning);

	void startTestCase(const TestCaseInfoReader* testCase);
	void endTestCase(const TestCaseInfoReader* testCase, unsigned int, unsigned int);

   WrittableChannel* channel; // Y
};

/////////////////////////////////////////////////////////////////////////
namespace
{
   const unsigned char startCmd   = 1;
   const unsigned char endCmd     = 2;
   const unsigned char errorCmd   = 3;
   const unsigned char failureCmd = 4;
   const unsigned char infoCmd    = 5;
   const unsigned char warnCmd    = 6;
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseError(const TestCaseInfoReader* testCase, const std::string& msg)
{
	channel->writeByte(errorCmd);
   channel->writeString(msg);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseFailure(const TestCaseInfoReader* testCase, const AssertionFailure& failure)
{
	channel->writeByte(failureCmd);
   channel->writeString(failure.getFileName());
   channel->writeInt(failure.getLineOfFile());
   channel->writeString(failure.what());
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseInfo(const TestCaseInfoReader* testCase, const Info& info)
{
   channel->writeByte(infoCmd);
   channel->writeString(info.getFileName());
   channel->writeInt(info.getLineOfFile());
   channel->writeString(info.what());
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseWarning(const TestCaseInfoReader* testCase, const Warning& warning)
{
   channel->writeByte(warnCmd);
   channel->writeString(warning.getFileName());
   channel->writeInt(warning.getLineOfFile());
   channel->writeString(warning.what());
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
startTestCase(const TestCaseInfoReader* testCase)
{
	channel->writeByte(startCmd);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
endTestCase(const TestCaseInfoReader* testCase, unsigned int secs, unsigned int usecs)
{
	channel->writeByte(endCmd);
   channel->writeInt(secs);
   channel->writeInt(usecs);
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultReporter::
TestCaseSandboxResultReporter(WrittableChannel* channel)
   : This(new TestCaseSandboxResultReporterImpl(channel))
{
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultReporter::~TestCaseSandboxResultReporter()
{
   delete This;
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseError(const TestCaseInfoReader* testCase, const std::string& msg)
{
	This->addCaseError(testCase, msg);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseFailure(const TestCaseInfoReader* testCase, const AssertionFailure& failure)
{
	This->addCaseFailure(testCase, failure);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseInfo(const TestCaseInfoReader* testcase, const Info& info)
{
   This->addCaseInfo(testcase, info);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseWarning(const TestCaseInfoReader* testcase, const Warning& warning)
{
   This->addCaseWarning(testcase, warning);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
startTestCase(const TestCaseInfoReader* testCase)
{
	This->startTestCase(testCase);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
endTestCase
      ( const TestCaseInfoReader* testCase
      , unsigned int secs
      , unsigned int usecs)
{
	This->endTestCase(testCase, secs, usecs);
}


TESTNGPP_NS_END

