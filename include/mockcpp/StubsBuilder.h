
#ifndef __MOCKCPP_STUBS_BUILDER_H
#define __MOCKCPP_STUBS_BUILDER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/InvocationMockBuilder.h>
#include <mockcpp/ArgumentsMatchBuilder.h>
#include <mockcpp/StubBuilder.h>
#include <mockcpp/MoreStubBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
typedef InvocationMockBuilder<
          ArgumentsMatchBuilder<
            StubBuilder< 
              MoreStubBuilder<>
            >
          >
        > StubsBuilder;

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

