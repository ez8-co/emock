
#include <mockcpp/AssertionFailedError.h>

MOCKCPP_NS_START

AssertionFailedError::AssertionFailedError (
        unsigned srcline
      , const char* srcfile
      , const std::string& message)
	: Exception(srcline, srcfile, message)
{
}

AssertionFailedError::~AssertionFailedError() throw()
{
}

void
assertionFailed(unsigned srcline, const char* srcfile,
                     const std::string& message)
{
	throw AssertionFailedError(srcline, srcfile, message);
}


MOCKCPP_NS_END

