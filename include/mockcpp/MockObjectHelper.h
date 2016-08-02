
#ifndef __MOCKCPP_MOCK_OBJECT_HELPER_H__
#define __MOCKCPP_MOCK_OBJECT_HELPER_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/MockObject.h>

#include <boost/typeof/typeof.hpp>

MOCKCPP_NS_START

template <typename MockObjectClass>
struct MockObjectTraits
{
   typedef typename MockObjectClass::MockedInterface TYPE;
};

MOCKCPP_NS_END

#define METHOD(m) method(&m, #m)

#define MOCK_METHOD(obj, m) \
   obj.method(&MOCKCPP_NS::MockObjectTraits<BOOST_TYPEOF(obj)>::TYPE::m, \
       (MOCKCPP_NS::TypeString< \
            MOCKCPP_NS::MockObjectTraits<BOOST_TYPEOF(obj)>::TYPE \
       >::value() + "::"#m).c_str()) 

#define MOCK_OVERLOAD_METHOD(obj, type, m) \
   obj.method((type) &MOCKCPP_NS::MockObjectTraits<BOOST_TYPEOF(obj)>::TYPE::m, \
       ("("#type")" + MOCKCPP_NS::TypeString< \
            MOCKCPP_NS::MockObjectTraits<BOOST_TYPEOF(obj)>::TYPE \
       >::value() + "::"#m).c_str())

#endif

