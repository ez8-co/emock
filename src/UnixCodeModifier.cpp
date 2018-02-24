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

#include <string.h>
#include <inttypes.h>
#include <sys/mman.h>

#include "CodeModifier.h"

#define PAGE_ALIGN_BITS  12

//////////////////////////////////////////////////////////////////
#define PAGE_SIZE   (1 << PAGE_ALIGN_BITS)
#define ALIGN_TO_PAGE_BOUNDARY(addr) (void*) (((uintptr_t)addr) >> PAGE_ALIGN_BITS << PAGE_ALIGN_BITS)
//////////////////////////////////////////////////////////////////

EMOCK_NS_START

bool CodeModifier::modify(void *dest, const void *src, size_t size)
{
    if(::mprotect(ALIGN_TO_PAGE_BOUNDARY(dest), PAGE_SIZE * 2, PROT_EXEC | PROT_WRITE | PROT_READ ) != 0)
    {  
       return false; 
    }

    ::memcpy(dest, src, size);


#if 0
	#if BUILD_FOR_X86
	//(void)memcpy(dest, src, size); // something wrong on linux: after memcpy(or 5 single byte copy),  the 4 bytes following jmp, src is 0x07c951b0, but dest is 0x07b851b0. so use unsigned int *, it works ok.
	*((unsigned char *)dest) = *((unsigned char *)src);
	*((unsigned long *)((unsigned long)dest + 1)) = *((unsigned long *)((unsigned long)src + 1));
	#else
	*((unsigned char *)dest) = *((unsigned char *)src);
	*((unsigned char *)((unsigned long)dest + 1)) = *((unsigned char *)((unsigned long)src + 1));
    // after this line, dest+2 is 0x00c90000, not 0, so change it.
	*((unsigned char *)((unsigned long)dest + 2)) = *((unsigned char *)((unsigned long)src + 2));
	*((unsigned char *)((unsigned long)dest + 3)) = *((unsigned char *)((unsigned long)src + 3));
	*((unsigned char *)((unsigned long)dest + 4)) = *((unsigned char *)((unsigned long)src + 4));
	*((unsigned char *)((unsigned long)dest + 5)) = *((unsigned char *)((unsigned long)src + 5));
	*((unsigned long *)((unsigned long)dest + 6)) = *((unsigned long *)((unsigned long)src + 6));
	#endif
#endif

	return true;
}


EMOCK_NS_END


