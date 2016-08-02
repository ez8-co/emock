
#include <mockcpp/OutBoundPointer.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////////////////
void OutBoundPointerCheckConst(const std::string& typeString, bool isConst) 
{
   oss_t oss;

   oss << "A constant pointer " << typeString
       << " cannot be outbounded";

   MOCKCPP_ASSERT_FALSE_MESSAGE( oss.str(), isConst);
}

////////////////////////////////////////////////////////////////////////////
OutBoundPointer<void*>::OutBoundPointer(void* p, size_t size, Constraint* constraint)
	 : OutBoundPointerBase<void*>(p, size, constraint)
{
	MOCKCPP_ASSERT_TRUE_MESSAGE(
            "parameter \"size\" of OutBoundPointer<void*> cannot be specified as 0",
            size > 0);
}

////////////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

