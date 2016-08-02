
#include <mockcpp/Exception.h>

MOCKCPP_NS_START

#if !defined(MOCKCPP_USING_CPPUNIT)

Exception::Exception (unsigned line, const char* file, const std::string& msg )
	: std::exception()
	, message(msg)
	, srcline(line)
	, srcfile(file)
{
}

//////////////////////////////////////////////////////
Exception::~Exception() throw()
{
}

//////////////////////////////////////////////////////
std::string Exception::getMessage() const
{
    return message;
}

//////////////////////////////////////////////////////
unsigned Exception::getSrcLine() const
{
    return srcline;
}

//////////////////////////////////////////////////////
std::string Exception::getSrcFile() const
{
    return srcfile;
}

//////////////////////////////////////////////////////
const char* Exception::what() const throw()
{
    what_helper = getMessage();
    return what_helper.c_str();
}

#endif

MOCKCPP_NS_END


