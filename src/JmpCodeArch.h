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
#ifndef __MOCKCPP_JMP_CODE_ARCH_H__
#define __MOCKCPP_JMP_CODE_ARCH_H__

#include <mockcpp/mockcpp.h>

#if BUILD_FOR_X64
# include "JmpCodeX64.h"
#elif BUILD_FOR_X86
# include "JmpCodeX86.h"
#endif

#endif

