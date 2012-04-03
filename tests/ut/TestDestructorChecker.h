
#include <testcpp/testcpp.hpp>

#include <mockcpp/DestructorChecker.h>

USING_MOCKCPP_NS
USING_TESTCPP_NS

class TestDestructorChecker: public TESTCPP_NS::TestFixture
{
   struct Interface { virtual void foo() = 0; virtual ~Interface() {} };

private:

   TESTCPP_RCP checkpoint;

public:

   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();
   }
   void tearDown()
   {
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToGetDestructorIndexWithoutMemoryLeaking()
   {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();
   }   
};
