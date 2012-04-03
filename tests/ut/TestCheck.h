/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
						  <Chen Guodong: sinojelly@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <testngpp/testngpp.hpp>
#include <mockcpp/mockcpp.hpp>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

typedef struct
{
	int a;
	int b;
}STRUCT_T;

struct Interface
{
	virtual void method(STRUCT_T *p) = 0;
	virtual ~Interface(){}
};

void client(Interface *interface, STRUCT_T *para)
{
	interface->method(para);
}

bool is_the_second_member_2(STRUCT_T *p)
{
	if (p->b == 2)
	{
		return true;
	}
	return false;
}

bool modify_the_first_member_to_10(STRUCT_T *p)
{
	p->a = 10;
	return true;
}

FIXTURE(Check)
{
	STRUCT_T input;
	MockObject<Interface> mocker;

	SETUP()
	{
		input.a = 1;
		input.b = 2;		
	}

	TEARDOWN()
	{
		mocker.verify();
		mocker.reset();
	}

	TEST(Can use function to check the specified member in structure)
	{
		MOCK_METHOD(mocker, method)
			.expects(once())
			.with(checkWith(is_the_second_member_2));
		
		client(mocker, &input);
	
	}

	// TODO: warning C4717: mockcpp::toString<bool __cdecl(STRUCT_T *)>
	#if 1
	TEST(If the second member is not expected => it should throw something)
	{
		STRUCT_T input = {1, 3};

		//MOCK_METHOD(mocker, method)
		//	.expects(once())
		//	.with(checkWith(is_the_second_member_2));

		//ASSERT_THROWS_ANYTHING(client(mocker, &input));

		//ASSERT_THROWS_ANYTHING(mocker.verify());

		//mocker.reset();
	}
	#endif


	struct the_second_member_checker 
	{
		the_second_member_checker(int __b)
		{
			b = __b;
		}
		bool operator()(STRUCT_T *p)
		{
			if (p->b == b)
			{
				return true;
			}
			return false;
		}
		int b;
	};
	

	TEST(Can use functor to check the specified member in structure)
	{
		MOCK_METHOD(mocker, method)
			.expects(once())
			.with(checkWith(the_second_member_checker(2)));

		client(mocker, &input);
	}


	TEST(Can modify the input s specified member)
	{
		MOCK_METHOD(mocker, method)
			.expects(once())
			.with(checkWith(modify_the_first_member_to_10));

		client(mocker, &input);

		ASSERT_EQ(10, input.a);
	}
};

