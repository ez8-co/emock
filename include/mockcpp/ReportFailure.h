
#ifndef __MOCKCPP_REPORT_FAILURE_H
#define __MOCKCPP_REPORT_FAILURE_H

#include <string>
#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

void
reportFailure
      ( unsigned int       line
      , const char*        file
      , const std::string& message);

#define MOCKCPP_REPORT_FAILURE(msg) \
   MOCKCPP_NS::reportFailure(__LINE__, __FILE__, msg)

#define MOCKCPP_ASSERT_FALSE(msg, expr) do {\
   if(expr) { \
      MOCKCPP_REPORT_FAILURE(msg); \
   } \
} while(0)

#define MOCKCPP_ASSERT_TRUE(msg, expr) do {\
   if(!(expr)) { \
      MOCKCPP_REPORT_FAILURE(msg); \
   } \
} while(0)

MOCKCPP_NS_END

#endif

