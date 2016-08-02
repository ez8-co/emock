
#ifndef __MOCKCPP_DEFAULT_BUIDLER_H_
#define __MOCKCPP_DEFAULT_BUIDLER_H_

#include <mockcpp/mockcpp.h>

#include <mockcpp/InvocationMockBuilder.h>
#include <mockcpp/CallerMatchBuilder.h>
#include <mockcpp/ArgumentsMatchBuilder.h>
#include <mockcpp/StubBuilder.h>
#include <mockcpp/MoreStubBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
typedef InvocationMockBuilder< 
         CallerMatchBuilder<
          ArgumentsMatchBuilder<
           StubBuilder<
            MoreStubBuilder<>
           >
          >
         >
        > DefaultBuilder;

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

