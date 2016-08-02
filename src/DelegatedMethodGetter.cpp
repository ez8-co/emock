/***
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

