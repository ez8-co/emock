
#include <mockcpp/mockcpp.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/ReportFailure.h>

MOCKCPP_NS_START

void maxVtblSizeTooBigError(unsigned int index)
{
   oss_t oss;

   oss << "VTBL index ("
       << index 
       << ") exceeds the limitation of configuration ("
       << MOCKCPP_MAX_VTBL_SIZE
       << ")";

   MOCKCPP_REPORT_FAILURE(oss.str());
}

void maxInheritanceTooBigError(unsigned int index)
{
   oss_t oss;

   oss << "VPTR index ("
       << index 
       << ") exceeds the limitation of inheritance("
       << MOCKCPP_MAX_INHERITANCE
       << ")";

   MOCKCPP_REPORT_FAILURE(oss.str());
}

MOCKCPP_NS_END

