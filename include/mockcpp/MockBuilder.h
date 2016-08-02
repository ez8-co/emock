
#ifndef __MOCKCPP_MOCK_BUILDER_H
#define __MOCKCPP_MOCK_BUILDER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/InvocationMockBuilder.h>
#include <mockcpp/CallerMatchBuilder.h>
#include <mockcpp/BeforeMatchBuilder.h>
#include <mockcpp/ArgumentsMatchBuilder.h>
#include <mockcpp/AfterMatchBuilder.h>
#include <mockcpp/StubBuilder.h>
#include <mockcpp/MoreStubBuilder.h>
#include <mockcpp/IdentityBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
typedef InvocationMockBuilder<
          CallerMatchBuilder<
           BeforeMatchBuilder<
            ArgumentsMatchBuilder<
             AfterMatchBuilder<
              StubBuilder< 
               MoreStubBuilder<
                IdentityBuilder
               >
              >
             >
            >
           >
          >
         > MockBuilder;

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

