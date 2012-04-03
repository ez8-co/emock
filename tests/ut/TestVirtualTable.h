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
#include <iostream>
#include <string>

#include <testcpp/testcpp.hpp>

#include <mockcpp/VirtualTable.h>
#include <mockcpp/IndexInvokableGetter.h>
#include <mockcpp/Invokable.h>
#include <mockcpp/Exception.h>
#include <mockcpp/MethodInfoReader.h>
#include <mockcpp/DestructorChecker.h>
#include <mockcpp/ObjNameGetter.h>

USING_MOCKCPP_NS

struct IndexInvokableGetterStub : public IndexInvokableGetter
{
	Invokable* getInvokable(unsigned int indexOfVtbl, unsigned int indexOfVptr = 0) const
   {
		return 0;
   }
};

struct TestMethodHolder
{
   long base11(bool p) const
   {
       return p?100:-100;
   }
};

class TestVirtualTable: public TESTCPP_NS::TestFixture
{
	struct Base0
   {
      virtual int  base00() = 0;
      virtual bool base01(int) const = 0;
      virtual ~Base0() {}
   };

   struct Base1
   {
      virtual void base10() = 0;
      virtual long base11(bool) const = 0;

      virtual ~Base1() {}
   };

   struct Interface: public Base0, public Base1
   {
      virtual void a() {}
      virtual void b(bool) {}
   };

   struct ThisObject : public ObjectNameGetter
   {
      ThisObject():name("object") {}
   
      const std::string& getName() const
      { return name; }

      const std::string name;
   };

private:

   TESTCPP_RCP checkpoint;

   IndexInvokableGetterStub indexInvokableGetter;

   VirtualTable* vtbl;

   Interface* pI;

   ThisObject object;

public:

   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

      vtbl = new VirtualTable(&indexInvokableGetter
                     , &object
                     , sizeof(Interface)/sizeof(void*)
                     , typeid(Interface));
      TS_ASSERT(vtbl != 0);

      // FIXME: pI will automatically become to 0!!!! wired!!!!
      Interface* pI = (Interface*) vtbl->toPointerToInterface();

   }

   void tearDown()
   {
      pI = 0;

      delete vtbl;

      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   template <typename Method>
   int getIndexOfMethod(Method m)
   {
      return MOCKCPP_NS::getIndexOfMethod<Interface, Method>(m);
   }

   template <typename Method>
   int getDeltaOfMethod(Method m)
   {
      return MOCKCPP_NS::getDeltaOfMethod<Interface, Method>(m);
   }

	/////////////////////////////////////////////////////////

   // @test
   void shouldBeAbleToConvertToPointerToInterfaceType()
   {
      Interface* p = (Interface*) vtbl->toPointerToInterface();

      TS_ASSERT_THROWS(p->a(), MOCKCPP_NS::Exception);
   }

   // @test
   void shouldThrowExceptionIfTheNumberOfVptrExceedsTheMaxSettingOfConfiguration()
   {
      TS_ASSERT_THROWS( new VirtualTable(&indexInvokableGetter
                      , &object
                      , 10 
                      , typeid(Interface)), MOCKCPP_NS::Exception);
   }

   // @test
   void shouldBeAbleToSetMethod()
   {
      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);

      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      vtbl->addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      Interface* p = (Interface*) vtbl->toPointerToInterface();

      TestMethodHolder holder;

      TS_ASSERT_EQUALS(p->base11(true), holder.base11(true));
      TS_ASSERT_EQUALS(p->base11(false), holder.base11(false));
      TS_ASSERT(p->base11(true) != p->base11(false));
   }

   // @test
   void shouldThrowExceptionIfAMethodIsNotSet()
   {
      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
      vtbl->addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      Interface* p = (Interface*) vtbl->toPointerToInterface();

      p->base11(true);

      TS_ASSERT_THROWS(p->base00(), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(p->base01(0), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(p->base10(), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(p->a(), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(p->b(true), MOCKCPP_NS::Exception);
   }

   // @test
   void shouldThrowExceptionIfIndexOfVtblExceedsTheLimitationOfConfiguration()
   {
      unsigned int indexOfVtbl = 20; //MOCKCPP_MAX_VTBL_SIZE;
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      TS_ASSERT_THROWS(vtbl->addMethod(methodAddr, indexOfVtbl, indexOfVptr), MOCKCPP_NS::Exception);
   }

   // @test
   void shouldThrowExceptionIfIndexOfVtblExceedsTheNumberOfVptr()
   {
      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = 5; //MOCKCPP_MAX_INHERITANCE;
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      TS_ASSERT_THROWS(vtbl->addMethod(methodAddr, indexOfVtbl, indexOfVptr), MOCKCPP_NS::Exception);
   }

   // @test
   void shouldBeAbleToGetPreviouslySetIndexInvokableGetterByReturnedPointerToInterface()
   {
      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      vtbl->addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      IndexInvokableGetter* getter = VirtualTable::getInvokableGetter(vtbl->toPointerToInterface(), 0);

      TS_ASSERT_EQUALS(getter, &indexInvokableGetter);
   }

   // @test
   void shouldThrowExceptionIfItExpectedToBeDeletedButActuallyNotWhenItIsVerified()
   {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();

      vtbl->setDestructor(indices.first, indices.second);
      vtbl->expectsBeingDeleted();

      TS_ASSERT_THROWS(vtbl->verify(), Exception);
    }

   // @test
    void shouldPassVerifyIfThePointerIsDeletedAsExpected()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();

      vtbl->setDestructor(indices.first, indices.second);
      vtbl->expectsBeingDeleted();

      Interface* p = (Interface*) vtbl->toPointerToInterface();
      delete p;

      TS_ASSERT_THROWS_NOTHING(vtbl->verify());
    }

    // @test
    void shouldPassVerifyIfThePointerIsNotDeletedAsExpected()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();

      vtbl->setDestructor(indices.first, indices.second);

      TS_ASSERT_THROWS_NOTHING(vtbl->verify());
    }

    // @test
    void shouldFailThrowExceptionWhileTryingToDeleteThePointerWhichWasExpectedNotTo()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();

      vtbl->setDestructor(indices.first, indices.second);
      vtbl->expectsKeepAlive();

      Interface* p = (Interface*) vtbl->toPointerToInterface();
      TS_ASSERT_THROWS(delete p, Exception);
    }

    // @test
    void shouldThrowExceptionIfAnObjectIsExpectedBothKeepAliveAndBeingDelete()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();

      vtbl->setDestructor(indices.first, indices.second);
      vtbl->expectsKeepAlive();
      TS_ASSERT_THROWS(vtbl->expectsBeingDeleted(), Exception);
    }

    // @test
    void shouldThrowExceptionIfAnObjectIsExpectedBothKeepAliveAndBeingDelete2()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();

      vtbl->setDestructor(indices.first, indices.second);
      vtbl->expectsBeingDeleted();
      TS_ASSERT_THROWS(vtbl->expectsKeepAlive(), Exception);
    }

    // @test
    void shouldThrowExceptionWhenTryingToExpectsADeletedObjectKeepAlive()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();
      vtbl->setDestructor(indices.first, indices.second);

      delete (Interface*) vtbl->toPointerToInterface();

      TS_ASSERT_THROWS(vtbl->expectsKeepAlive(), Exception);
    }

    // @test
    void shouldThrowAnExceptionWhenTryingToAccessMethodsOfADeleteObject()
    {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<Interface, Interface>();
      vtbl->setDestructor(indices.first, indices.second);

      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
      vtbl->addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      Interface* p = (Interface*) vtbl->toPointerToInterface();
      delete p;

      TS_ASSERT_THROWS(VirtualTable::getInvokableGetter(vtbl->toPointerToInterface(), 0), Exception);
    }
};

