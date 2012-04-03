
#include <string>
#include <sstream>

#include <testcpp/testcpp.hpp>

#include <mockcpp/Invokable.h>

#include <mockcpp/ChainableMockMethod.h>
#include <mockcpp/ChainingMockHelper.h>

USING_MOCKCPP_NS
USING_TESTCPP_NS

class TestChainableMockMethod: public TESTCPP_NS::TestFixture
{
   struct InvokableStub : public Invokable
   {

    InvokableStub(const std::string& returned)
      : stub(returnValue(returned))
    {}

    ~InvokableStub()
    {
       delete stub;
    }

    const Any& invoke( const std::string& nameOfCaller
              , const RefAny& p1
              , const RefAny& p2
              , const RefAny& p3
              , const RefAny& p4
              , const RefAny& p5
              , const RefAny& p6
              , const RefAny& p7
              , const RefAny& p8
              , const RefAny& p9
              , const RefAny& p10
              , const RefAny& p11
              , const RefAny& p12
              , SelfDescribe* &resultProvider)
     {
        Invocation inv(nameOfCaller, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
        return stub->invoke(inv); 
     }

     Stub* stub;
   };

private:

   TESTCPP_RCP checkpoint;
   Invokable* invokable;

public:

   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();
      invokable = new InvokableStub("abcdefg");
   }

   void tearDown()
   {
      delete invokable;
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   // @test
   void shouldBeAbleToReturnAReferenceType()
   {
      ChainableMockMethod<const std::string&> method(invokable);
      std::string str = method(__FUNCTION__);
      TS_ASSERT_EQUALS(std::string("abcdefg"), str);
   }

   // @test
   void shouldBeAbleToReturnAReferenceTypeDirectly()
   {
      ChainableMockMethod<const std::string&> method(invokable);
      TS_ASSERT_EQUALS(std::string("abcdefg"), method(__FUNCTION__));
   }
};
