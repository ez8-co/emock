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

#ifndef __MOCKCPP_VIRTUAL_TABLE_UTILS_H
#define __MOCKCPP_VIRTUAL_TABLE_UTILS_H

#include <typeinfo>
#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

void** createVtbls(unsigned int numberOfVptr);
void freeVtbls(void** vtbl, unsigned int numberOfVtpr);
unsigned int getRealVtblIndex(unsigned int indexOfVptr, unsigned int indexOfVtbl);
void initializeVtbls(void** vptr, void**vtbl, unsigned int numberOfVtpr, const std::type_info& info, bool hasRtti);

MOCKCPP_NS_END

#endif
