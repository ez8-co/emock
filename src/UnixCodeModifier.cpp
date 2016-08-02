***/

#include <string.h>
#include <inttypes.h>
#include <sys/mman.h>

#include <mockcpp/CodeModifier.h>

#define PAGE_ALIGN_BITS  12

//////////////////////////////////////////////////////////////////
#define PAGE_SIZE   (1 << PAGE_ALIGN_BITS)
#define ALIGN_TO_PAGE_BOUNDARY(addr) (void*) (((uintptr_t)addr) & (~((1<<(PAGE_ALIGN_BITS))-1)))
//////////////////////////////////////////////////////////////////

MOCKCPP_NS_START

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


MOCKCPP_NS_END


