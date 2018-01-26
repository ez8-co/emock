/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.

   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#if defined(__GNUC__)

#include <cxxabi.h>

#include <emock/emock.h>
#include <emock/Exception.h>
#include <emock/ReportFailure.h>

using namespace __cxxabiv1;

EMOCK_NS_START

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
      EMOCK_REPORT_FAILURE("virtual inheritance of interfaces is not" \
                  " a good practice, hence, mockcpp does not support it");
   }

   if(!(info.__offset_flags & __base_class_type_info::__public_mask))
   {
      EMOCK_REPORT_FAILURE("non-public inheritance of interfaces is not" \
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
      EMOCK_REPORT_FAILURE("Diamond inheritance of interfaces is not" \
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
      EMOCK_REPORT_FAILURE("the type you are trying to mock is not a class.");
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

EMOCK_NS_END

#endif

