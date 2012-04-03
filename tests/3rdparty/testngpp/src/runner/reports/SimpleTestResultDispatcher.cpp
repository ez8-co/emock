
#include <list>
#include <iostream>

#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TagsFilterRule.h>

#include <testngpp/listener/TestListener.h>
#include <testngpp/listener/TestCaseListener.h>
#include <testngpp/listener/TestSuiteListener.h>

#include <testngpp/runner/SimpleTestResultDispatcher.h>

TESTNGPP_NS_START

///////////////////////////////////////////////////////////
struct SimpleTestResultDispatcherImpl
{
   typedef std::list<TestListener*> Listeners;
   typedef std::list<TestCaseListener*> CaseListeners;
   typedef std::list<TestSuiteListener*> SuiteListeners;

   Listeners listeners;
   CaseListeners caseListeners;
   SuiteListeners suiteListeners;

   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);
   void addCaseWarning(const TestCaseInfoReader*, const Warning&);
   void addCaseInfo(const TestCaseInfoReader*, const Info&);

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
   void endTest(unsigned int secs, unsigned int usecs);
   void addError(const std::string&);
   
};

///////////////////////////////////////////////////////////
SimpleTestResultDispatcher::SimpleTestResultDispatcher()
   : This(new SimpleTestResultDispatcherImpl)
{}

///////////////////////////////////////////////////////////
SimpleTestResultDispatcher::~SimpleTestResultDispatcher()
{
   delete This;
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
registerListener(TestListener* listener)
{
   if(listener == 0)
   {
      return;
   }

   This->listeners.push_back(listener);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
registerTestCaseListener(TestCaseListener* listener)
{
   if(listener == 0)
   {
      return;
   }

   This->caseListeners.push_back(listener);
}

///////////////////////////////////////////////////////////
TestCaseListener* SimpleTestResultDispatcher::
unregisterTestCaseListener(TestCaseListener* listener)
{
   This->caseListeners.remove(listener);
   return listener;
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
registerTestSuiteListener(TestSuiteListener* listener)
{
   if(listener == 0)
   {
      return;
   }

   This->suiteListeners.push_back(listener);
}

///////////////////////////////////////////////////////////
TestSuiteListener*
SimpleTestResultDispatcher::
unregisterTestSuiteListener(TestSuiteListener* listener)
{
   This->suiteListeners.remove(listener);
   return listener;
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseCrash(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseCrash(testcase);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   notifyAddCaseCrash(caseListeners, testcase);
   notifyAddCaseCrash(suiteListeners, testcase);
   notifyAddCaseCrash(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   This->addCaseCrash(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseSkipped(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseSkipped(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   notifyAddCaseSkipped(caseListeners, testcase);
   notifyAddCaseSkipped(suiteListeners, testcase);
   notifyAddCaseSkipped(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   This->addCaseSkipped(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseError(T& listeners, 
   const TestCaseInfoReader* testcase, const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseError(testcase, msg);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
   notifyAddCaseError(caseListeners, testcase, msg);
   notifyAddCaseError(suiteListeners, testcase, msg);
   notifyAddCaseError(listeners, testcase, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
   This->addCaseError(testcase, msg);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseFailure(T& listeners, 
   const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseFailure(testcase, failure);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   notifyAddCaseFailure(caseListeners, testcase, failure);
   notifyAddCaseFailure(suiteListeners, testcase, failure);
   notifyAddCaseFailure(listeners, testcase, failure);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   This->addCaseFailure(testcase, failure);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseWarning(T& listeners,
   const TestCaseInfoReader* testcase, const Warning& warning)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseWarning(testcase, warning);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseWarning(const TestCaseInfoReader* testcase, const Warning& warning)
{
   notifyAddCaseWarning(caseListeners, testcase, warning);
   notifyAddCaseWarning(suiteListeners, testcase, warning);
   notifyAddCaseWarning(listeners, testcase, warning);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseWarning(const TestCaseInfoReader* testcase, const Warning& warning)
{
   This->addCaseWarning(testcase, warning);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseInfo(T& listeners,
   const TestCaseInfoReader* testcase, const Info& info)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseInfo(testcase, info);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseInfo(const TestCaseInfoReader* testcase, const Info& info)
{
   notifyAddCaseInfo(caseListeners, testcase, info);
   notifyAddCaseInfo(suiteListeners, testcase, info);
   notifyAddCaseInfo(listeners, testcase, info);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseInfo(const TestCaseInfoReader* testcase, const Info& info)
{
   This->addCaseInfo(testcase, info);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartCase(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestCase(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestCase(const TestCaseInfoReader* testcase)
{
   notifyStartCase(caseListeners, testcase);
   notifyStartCase(suiteListeners, testcase);
   notifyStartCase(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestCase(const TestCaseInfoReader* testcase)
{
   This->startTestCase(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndCase
      ( T& listeners
      , const TestCaseInfoReader* testcase
      , unsigned int secs
      , unsigned int usecs)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestCase(testcase, secs, usecs);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestCase
      ( const TestCaseInfoReader* testcase
      , unsigned int secs
      , unsigned int usecs)
{
   notifyEndCase(caseListeners, testcase, secs, usecs);
   notifyEndCase(suiteListeners, testcase, secs, usecs);
   notifyEndCase(listeners, testcase, secs, usecs);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestCase
      ( const TestCaseInfoReader* testcase
      , unsigned int secs
      , unsigned int usecs)
{
   This->endTestCase(testcase, secs, usecs);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartFixture(T& listeners, TestFixtureInfoReader* fixture)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestFixture(fixture);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestFixture(TestFixtureInfoReader* fixture)
{
   notifyStartFixture(suiteListeners, fixture);
   notifyStartFixture(listeners, fixture);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestFixture(TestFixtureInfoReader* fixture)
{
   This->startTestFixture(fixture);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndFixture(T& listeners, TestFixtureInfoReader* fixture)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestFixture(fixture);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestFixture(TestFixtureInfoReader* fixture)
{
   notifyEndFixture(suiteListeners, fixture);
   notifyEndFixture(listeners, fixture);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestFixture(TestFixtureInfoReader* fixture)
{
   This->endTestFixture(fixture);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddFixtureError(T& listeners
       , TestFixtureInfoReader* fixture
       , const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addFixtureError(fixture, msg);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addFixtureError( TestFixtureInfoReader* fixture
               , const std::string& msg)
{
   notifyAddFixtureError(suiteListeners, fixture, msg);
   notifyAddFixtureError(listeners, fixture, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addFixtureError(TestFixtureInfoReader* fixture, const std::string& msg)
{
   This->addFixtureError(fixture, msg);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddFixtureFailure(T& listeners
       , TestFixtureInfoReader* fixture
       , const AssertionFailure& failure)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addFixtureFailure(fixture, failure);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure)
{
   notifyAddFixtureFailure(suiteListeners, fixture, failure);
   notifyAddFixtureFailure(listeners, fixture, failure);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure)
{
   This->addFixtureFailure(fixture, failure);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartSuite(T& listeners
       , TestSuiteInfoReader* suite)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestSuite(suite);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestSuite(TestSuiteInfoReader* suite)
{
   notifyStartSuite(suiteListeners, suite);
   notifyStartSuite(listeners, suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestSuite(TestSuiteInfoReader* suite)
{
   This->startTestSuite(suite);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndSuite(T& listeners
       , TestSuiteInfoReader* suite)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestSuite(suite);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestSuite(TestSuiteInfoReader* suite)
{
   notifyEndSuite(suiteListeners, suite);
   notifyEndSuite(listeners, suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->endTestSuite(suite);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifySuiteError(T& listeners
       , TestSuiteInfoReader* suite
       , const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addSuiteError(suite, msg);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg )
{
   notifySuiteError(suiteListeners, suite, msg);
   notifySuiteError(listeners, suite, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg )
{
   This->addSuiteError(suite, msg);
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcherImpl::
startTagsFiltering(const TagsFilterRule* filter)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTagsFiltering(filter);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
startTagsFiltering(const TagsFilterRule* filter)
{
   This->startTagsFiltering(filter);
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcherImpl::
endTagsFiltering(const TagsFilterRule* filter) 
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTagsFiltering(filter);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
endTagsFiltering(const TagsFilterRule* filter) 
{
   This->endTagsFiltering(filter);
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcherImpl::
startTest()
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTest();
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::startTest()
{
   This->startTest();
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTest(unsigned int secs, unsigned int usecs)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTest(secs, usecs);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
endTest(unsigned int secs, unsigned int usecs)
{
   This->endTest(secs, usecs);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addError(const std::string& msg)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addError(msg);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
addError(const std::string& msg)
{
   This->addError(msg);
}

///////////////////////////////////////////////////////////

TESTNGPP_NS_END
