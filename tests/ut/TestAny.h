/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

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

#include <limits>

#include <testcpp/testcpp.hpp>
#include <mockcpp/types/Any.h>
#include <mockcpp/types/RefAny.h>
#include <mockcpp/types/AnyCast.h>
#include <mockcpp/IsRef.h>

USING_MOCKCPP_NS
          
#if 0
#define DATA_GROUP(data,...) { data, ##__VA_ARGS__}
#define DATA_PROVIDER(name, items, data1, ...)\
const Any getDataProvider##name(unsigned int index, unsigned int item) \
{ \
   const Any name[][items] = {data1, ##__VA_ARGS__}; \
   return name[index][item]; \
}
#endif

struct TestAny: public TESTCPP_NS::TestFixture 
{
#if 0
   DATA_PROVIDER
            ( myData, 3
            , DATA_GROUP(1, 1.0, (const char*)"abc")
            , DATA_GROUP(2, 2.1, (const char*)"cde")
            );

   TEST($> get data from data provider)
   {
      ASSERT_TRUE(any_castable<int>(getDataProvidermyData(0,0)));

      ASSERT_EQ(1, any_cast<int>(getDataProvidermyData(0, 0)));
      ASSERT_EQ(2, any_cast<int>(getDataProvidermyData(1, 0)));

      ASSERT_EQ(1.0, any_cast<double>(getDataProvidermyData(0, 1)));
      ASSERT_EQ(2.1, any_cast<double>(getDataProvidermyData(1, 1)));

      ASSERT_EQ((const char*)"abc", any_cast<const char*>(getDataProvidermyData(0, 2)));
      ASSERT_EQ((const char*)"cde", any_cast<const char*>(getDataProvidermyData(1, 2)));
   }
#endif

   // @test
	void ShouldBeEmptyIfANewInstanceIsNotInitialized()
	{
		Any i;

		TS_ASSERT(i.empty());
	}

   // @test
	void ShouldNotBeEmptyIfAInstanceIsInitialized()
	{
		Any i(0);

		TS_ASSERT(!i.empty());
	}

   // @test
	void ShouldBeCastableForSameType()
	{
		RefAny ref(10);

		TS_ASSERT(any_castable<int>(ref));
	}

   // @test
   void ShouldBeAbleStorePChar()
   {
		RefAny ref((char*)"abcd");

		TS_ASSERT(any_castable<char*>(ref));
   }
   
   // @test
   void ShouldBeAbleStoreNullPchar()
   {
		RefAny ref((char*)0);

		TS_ASSERT(any_castable<char*>(ref));
   }

   // @test
   void ShouldBeAbleCastUnsignedCharToUnsignedShort()
   {
      Any a((unsigned char)12);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(12, any_cast<unsigned short>(a));
   }

   // @test
   void ShouldBeAbleCastNonnegtiveShortToUnsignedShort()
   {
      Any a((short)5);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned short>(a));
   }

   // @test
   void ShouldBeAbleCastNonnegtiveCharToUnsignedShort()
   {
      Any a((char)2);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(2, any_cast<unsigned short>(a));
   }

   // @test
   void ShouldBeAbleCastUnsignedIntWithinLimitationToUnsignedShort()
   {
      Any a(65535);

      TS_ASSERT(any_castable<unsigned short>(a));
      TS_ASSERT_EQUALS(65535, any_cast<unsigned short>(a));
   }

   // @test
   void ShouldNotCastUnsignedIntExceedingTheLimitationToUnsignedShort()
   {
      Any a(65536);

      TS_ASSERT(!any_castable<unsigned short>(a));
   }

   // @test
   void ShouldBeAbleCastUnsignedShortToUnsignedInt()
   {
      Any a((unsigned short)15);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(15, any_cast<unsigned int>(a));
   }

   // @test
   void ShouldBeAbleCastUnsignedCharToUnsignedInt()
   {
      Any a((unsigned char)12);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(12, any_cast<unsigned int>(a));
   }

   // @test
   void ShouldBeAbleCastNonnegtiveIntToUnsignedInt()
   {
      Any a(1);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(1, any_cast<unsigned int>(a));
   }

   // @test
   void ShouldBeAbleCastNonnegtiveShortToUnsignedInt()
   {
      Any a((short)5);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned int>(a));
   }

   // @test
   void ShouldBeAbleCastNonnegtiveCharToUnsignedInt()
   {
      Any a((char)2);

      TS_ASSERT(any_castable<unsigned int>(a));
      TS_ASSERT_EQUALS(2, any_cast<unsigned int>(a));
   }

   // @test
   void ShouldBeAbleCastNonnegtiveIntToUnsignedLong()
   {
      Any a(1);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(1, any_cast<unsigned long>(a));
   }

   // @test
   void ShouldBeAbleToCastNonnegtiveShortToUnsignedLong()
   {
      Any a((short)5);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned long>(a));
   }

   // @test
   void ShouldBeAbleToCastNonnegtiveCharToUnsignedLong()
   {
      Any a((char)2);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(2, any_cast<unsigned long>(a));
   }

   // @test
   void ShouldBeAbleToCastNonnegtiveIntToUnsignedLong()
   {
      Any a((int)5);

      TS_ASSERT(any_castable<unsigned long>(a));
      TS_ASSERT_EQUALS(5, any_cast<unsigned long>(a));
   }

   // @test
   void ShouldBeAbleToCastInScopeUnsignedCharToChar()
   {
      Any a((unsigned char)std::numeric_limits<char>::max());

      TS_ASSERT(any_castable<char>(a));
      TS_ASSERT_EQUALS(std::numeric_limits<char>::max(), any_cast<char>(a));
   }

   // @test
   void ShouldNotCastInScopeUnsignedCharToChar()
   {
      Any a((unsigned char)std::numeric_limits<char>::max()+1);

      TS_ASSERT(!any_castable<char>(a));
   }

   // @test
   void ShouldBeAbleToCastInScopeUnsignedShortToShort()
   {
      Any a((unsigned short)32767);

      TS_ASSERT(any_castable<short>(a));
      TS_ASSERT_EQUALS(32767, any_cast<short>(a));
   }

   // @test
   void ShouldNotCastInScopeUnsignedShortToShort()
   {
      Any a((unsigned short)32768);

      TS_ASSERT(!any_castable<short>(a));
   }

   // @test
   void ShouldBeAbleToCastInScopeUnsignedIntToInt()
   {
      Any a((unsigned int)std::numeric_limits<int>::max());

      TS_ASSERT(any_castable<int>(a));
      TS_ASSERT_EQUALS(std::numeric_limits<int>::max(), any_cast<int>(a));
   }

   // @test
   void ShouldNotCastInScopeUnsignedIntToInt()
   {
      Any a((unsigned int)std::numeric_limits<int>::max()+1);

      TS_ASSERT(!any_castable<int>(a));
   }

   // @test
   void ShouldBeAbleToCastInScopeUnsignedLongToLong()
   {
      Any a((unsigned long)std::numeric_limits<long>::max());

      TS_ASSERT(any_castable<long>(a));
      TS_ASSERT_EQUALS(std::numeric_limits<long>::max(), any_cast<long>(a));
   }

   // @test
   void ShouldNotCastInScopeUnsignedLongToLong()
   {
      Any a((unsigned long)std::numeric_limits<long>::max()+1);

      TS_ASSERT(!any_castable<long>(a));
   }

   // @test
   void ShouldBeAbleToGetTypeAndValueString()
   {
      const std::string& str = std::string("abcdef");
      RefAny ref(str);

      TS_ASSERT_EQUALS(std::string("\"") + str + std::string("\""), ref.toString());
   }

   // @test
   void ShouldBeAbleToAnyCastReferenceCorrectly()
   {
      const std::string& str = std::string("abcdef");
      Any i(str);
      Any& ref = i;

      const std::string& result = any_cast<const std::string&>(ref);
      TS_ASSERT_EQUALS(std::string("abcdef"), result);
   }

   enum Enum { Enum10 = 10 };

   // @test
   void ShouldBeAbleToEnumToSameEnum()
   {
      Any e(Enum10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(e));
   }

   // @test
   void ShouldBeAbleToCastLongToEnum()
   {
      Any l((long)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(l));
   }

   // @test
   void ShouldBeAbleToCastIntToEnum()
   {
      Any i((int)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(i));
   }

   // @test
   void ShouldBeAbleToCastShortToEnum()
   {
      Any s((short)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(s));
   }

   // @test
   void ShouldBeAbleToCastCharToEnum()
   {
      Any c((char)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(c));
   }

   // @test
   void shouldBeAbleToCastUnsignedLongToEnum()
   {
      Any l((unsigned long)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(l));
   }

   // @test
   void ShouldBeAbleToCastUnsignedIntToEnum()
   {
      Any i((unsigned int)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(i));
   }

   // @test
   void ShouldBeAbleToCastUnsignedShortToEnum()
   {
      Any s((unsigned short)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(s));
   }

   // @test
   void ShouldBeAbleToCastUnsignedCharToEnum()
   {
      Any c((unsigned char)10);

      TS_ASSERT_EQUALS(Enum10, any_cast<Enum>(c));
   }

   TEST(castable_unsigned_int)
   {
      Any ui((unsigned int)2);
      TS_ASSERT(any_castable<unsigned int>(ui));
   }

   TEST(define Any array)
   {
      Any objects[] = {1, (const char*)"string", 1.2};

      ASSERT_EQ(1, any_cast<int>(objects[0]));
      ASSERT_EQ(1, any_cast<unsigned int>(objects[0]));

      ASSERT_EQ((const char*)"string", any_cast<const char*>(objects[1]));
      ASSERT_EQ(1.2, any_cast<double>(objects[2]));
   }
};

