
#ifndef __MOCKCPP_ASSERTION_FAILED_ERROR_H
#define __MOCKCPP_ASSERTION_FAILED_ERROR_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Exception.h>

MOCKCPP_NS_START

struct AssertionFailedError : public Exception
{
    AssertionFailedError (unsigned srcline, const char* srcfile,
                          const std::string& message);

    virtual ~AssertionFailedError() throw();
};

void
assertionFailed
      ( unsigned int       line
      , const char*        file
      , const std::string& message);

MOCKCPP_NS_END

#endif

