
#include <testcpp/testcpp.hpp>

#include <mockcpp/InterfaceInfo.h>
#include <mockcpp/Exception.h>

USING_MOCKCPP_NS
USING_TESTCPP_NS

class TestInterfaceInfo: public TESTCPP_NS::TestFixture
{
   struct Base0 { virtual void base0() {}; virtual ~Base0() {} };
   struct Base1 { virtual ~Base1() {} };

   struct Derived0 : public Base0 {};
   struct Derived1 : public Base0 {};

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

   void testShouldBeAbleCalculateNumberOfVptr_SingleInheritance()
   {
      TS_ASSERT_EQUALS(1, getNumberOfVtbls<Derived0>());
   }

   struct Derived2 : public Base0, public Base1 {};

   void testShouldBeAbleCalculateNumberOfVptr_MultiInheritance()
   {
      TS_ASSERT_EQUALS(2, getNumberOfVtbls<Derived2>());
   }

   struct Derived3 : public Derived0, public Derived1 {};
   struct Derived4 : public Derived3 {};

   void testShouldBeAbleCalculateTheNumberOfVptr_MultiInheritance2()
   {
      TS_ASSERT_EQUALS(sizeof(Derived4)/sizeof(void*), getNumberOfVtbls<Derived4>());
   }

   struct Derived5 : public Derived2, public Derived0 {};
   void testShouldBeAbleToCalculateTheNumberOfVptr_DupInheritance()
   {
      TS_ASSERT_EQUALS(sizeof(Derived5)/sizeof(void*), getNumberOfVtbls<Derived5>());
   }
 
   struct Derived6 : virtual public Derived2, virtual public Derived0 {};
   void testShouldBeThrowExcpetion_VirtualInheritance()
   {
      #ifndef _MSC_VER
	  //VC does not support
      TS_ASSERT_THROWS(getNumberOfVtbls<Derived6>(), MOCKCPP_NS::Exception);
	  #endif
   }
};
