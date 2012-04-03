
#ifndef __TESTNGPP_TESTCASE_HEIRARCHY_H
#define __TESTNGPP_TESTCASE_HEIRARCHY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCaseHierarchyImpl;
struct TestFixtureDesc;
struct TestCaseFilter;
struct TestCaseContainer;

struct TestCaseHierarchy
{
public:

   TestCaseHierarchy
         ( const TestFixtureDesc* fixture
         , const TestCaseFilter* filter);

   ~TestCaseHierarchy();

   void
   getDirectSuccessors
         ( const TestCase* testcase
         , TestCaseContainer* container);

   void
   getSuccessors
         ( const TestCase* testcase
         , TestCaseContainer* container);
private:
   TestCaseHierarchyImpl *This;
};

TESTNGPP_NS_END

#endif

