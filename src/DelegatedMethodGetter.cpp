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

#include <emock/emock.h>
#include <emock/OutputStringStream.h>
#include <emock/ReportFailure.h>

EMOCK_NS_START

void maxVtblSizeTooBigError(unsigned int index)
{
   oss_t oss;

   oss << "VTBL index ("
       << index 
       << ") exceeds the limitation of configuration ("
       << EMOCK_MAX_VTBL_SIZE
       << ")";

   EMOCK_REPORT_FAILURE(oss.str());
}

void maxInheritanceTooBigError(unsigned int index)
{
   oss_t oss;

   oss << "VPTR index ("
       << index 
       << ") exceeds the limitation of inheritance("
       << EMOCK_MAX_INHERITANCE
       << ")";

   EMOCK_REPORT_FAILURE(oss.str());
}

EMOCK_NS_END

