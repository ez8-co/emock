
#if defined(__GNUC__)

#include <cxxabi.h>

#include <mockcpp/mockcpp.h>
#include <mockcpp/Exception.h>
#include <mockcpp/ReportFailure.h>

using namespace __cxxabiv1;

MOCKCPP_NS_START

//////////////////////////////////////////////////////
unsigned int
getNumberOfBaseClassesByClassTypeInfo(
     const __class_type_info* info, unsigned int number);

//////////////////////////////////////////////////////
static unsigned int
getNumberOfVtblsByBaseClassTypeInfo(const __base_class_type_info& info
    , unsigned int number)
{
   if(info.__offset_flags & __base_class_type_info::__virtual_mask)
   {
      MOCKCPP_REPORT_FAILURE("virtual inheritance of interfaces is not" \
                  " a good practice, hence, mockcpp does not support it");
   }

   if(!(info.__offset_flags & __base_class_type_info::__public_mask))
   {
      MOCKCPP_REPORT_FAILURE("non-public inheritance of interfaces is not" \
                  " a good practice, hence, mockcpp does not support it");
   }

   return getNumberOfBaseClassesByClassTypeInfo(info.__base_type, number);
}

//////////////////////////////////////////////////////
unsigned int
getNumberOfVtblsByVmi(const __vmi_class_type_info* vmi, unsigned int number)
{
   if(vmi->__flags&__vmi_class_type_info::__diamond_shaped_mask)
   {
      MOCKCPP_REPORT_FAILURE("Diamond inheritance of interfaces is not" \
                  " a good practice, hence, mockcpp does not support it");
   }

   number = getNumberOfVtblsByBaseClassTypeInfo(vmi->__base_info[0], number);

   for(unsigned int i = 1; i < vmi->__base_count; i++)
   {
      number += getNumberOfVtblsByBaseClassTypeInfo(vmi->__base_info[i], 0);
   }

   return number;
}

//////////////////////////////////////////////////////
unsigned int
getNumberOfVtblsBySi(const __si_class_type_info* info, unsigned int number)
{
   if(info->__base_type == 0)
   {
      return number + 1;
   }

   return getNumberOfBaseClassesByClassTypeInfo(info->__base_type, number);
}

//////////////////////////////////////////////////////
unsigned int
getNumberOfBaseClasses(const std::type_info& info)
{
   try
   {
      const __class_type_info& classTypeInfo = \
         dynamic_cast<const __class_type_info&>(info);

      return getNumberOfBaseClassesByClassTypeInfo(&classTypeInfo, 0);
   }
   catch(std::bad_cast& e)
   {
      MOCKCPP_REPORT_FAILURE("the type you are trying to mock is not a class.");
   }

   return 0;
}

//////////////////////////////////////////////////////
unsigned int
getNumberOfBaseClassesByClassTypeInfo(const __class_type_info* info, unsigned int number)
{
   const __vmi_class_type_info* vmi_base_info = dynamic_cast<const __vmi_class_type_info*>(info);
   if(vmi_base_info != 0)
   {
	return getNumberOfVtblsByVmi(vmi_base_info, number);
   }

   const __si_class_type_info* si_base_info = dynamic_cast<const __si_class_type_info*>(info);
   if(si_base_info != 0)
   {
	return getNumberOfVtblsBySi(si_base_info, number);
   }
   
   return number + 1;
}

MOCKCPP_NS_END

#endif

