#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>
#include <mockcpp/mockcpp.hpp>

struct Interface
{
    virtual int method() = 0;
    static int func() { return 0; }
    virtual ~Interface(){}
};

int func_stub()
{
    return 1000;
}

FIXTURE(mockcpp_sample, mockcpp samples)
{
    TEST(test_method_mocker)
    {
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, method)
            .expects(once())
            .will(returnValue(10));
        ASSERT_EQ(10, mocker->method());
        mocker.verify();
    }

    TEST(test_func_mocker)
    {
        MOCKER(Interface::func)
            .expects(once())
            .will(returnValue(10));
        ASSERT_EQ(10, Interface::func());
        GlobalMockObject::verify();
    }
	
    TEST(test will invoke)
    {
        MOCKER(Interface::func)
            .expects(once())
            .will(invoke(func_stub));
        ASSERT_EQ(1000, Interface::func());
        GlobalMockObject::verify();
    }	
};
