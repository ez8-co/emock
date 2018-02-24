/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
***/

#include <list>
#include <cmath>
#include <string.h>

#include "Trampoline.h"
#include <emock/ReportFailure.h>
#include <emock/ArgumentsMacroHelpers.h>

#ifdef _MSC_VER

    #include <windows.h>
	#include <cassert>

#else

    #include <sys/mman.h>
    #include <inttypes.h>
    #include <stdio.h>
    #include <linux/limits.h>

#endif

EMOCK_NS_START

namespace {

    struct TrampolineInfo
    {
        unsigned char* base;
        size_t size;
        size_t used;
    };

    static std::list<TrampolineInfo> g_trampolines;

#define PAGE_ALIGN_BITS  12
#define PAGE_SIZE        (1 << PAGE_ALIGN_BITS)

static const size_t kMaxAllocationDelta = 0x80000000; // 2GB
static const size_t kAllocationSize     = PAGE_SIZE;  // 4KB

#ifdef _MSC_VER

    #if BUILD_FOR_X64
        #define _ADDRESS_MAX_VALUE 0x80000000000
    #elif BUILD_FOR_X86
        #define _ADDRESS_MAX_VALUE  0x100000000
    #endif

    void* TrampolineAllocateImpl(const unsigned char* dst, size_t alloc_size)
    {
        if((size_t)dst < 0)
            dst = NULL;

		const unsigned char* end = dst + kMaxAllocationDelta;

        MEMORY_BASIC_INFORMATION mbi = {0};
        for (; dst < end; dst += mbi.RegionSize)
        {
            if (!VirtualQuery((LPCVOID)dst, &mbi, sizeof(mbi)))
                break;

            assert(mbi.RegionSize != 0);

            if (mbi.State != MEM_FREE)
                continue;

            if ((unsigned long long)mbi.AllocationBase + mbi.RegionSize > _ADDRESS_MAX_VALUE)
                break;

            if (void* allocated = VirtualAlloc(mbi.AllocationBase, alloc_size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE))
                return allocated;
        }
        return NULL;
    }

    void* TrampolineAllocate(const unsigned char* dst, size_t alloc_size)
    {
        void* allocated = TrampolineAllocateImpl(dst - kMaxAllocationDelta, alloc_size);
        if(!allocated)
            allocated = TrampolineAllocateImpl(dst, alloc_size);

        if (allocated)
        {
            if (std::abs((long)dst - (long)allocated) > kMaxAllocationDelta)
            {
                VirtualFree(allocated, 0, MEM_RELEASE);
                return NULL;
            }
        }
        return allocated;
    }

    inline void TrampolineFree(unsigned char* allocated, size_t alloc_size)
    {
        VirtualFree(allocated, 0, MEM_RELEASE);
    }

#else

    #define ALIGN_TO_PAGE_BOUNDARY(addr) (void*) (((uintptr_t)addr) >> PAGE_ALIGN_BITS << PAGE_ALIGN_BITS)

    void* TrampolineAllocateImpl(const unsigned char* dst, size_t alloc_size)
    {
        void *allocated = ::mmap(ALIGN_TO_PAGE_BOUNDARY(dst), alloc_size, PROT_NONE,
                       MAP_PRIVATE | MAP_NORESERVE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
        if (allocated == MAP_FAILED)
            return NULL;
        if(::mprotect(allocated, alloc_size, PROT_EXEC | PROT_WRITE | PROT_READ ) != 0)  
           return NULL;
        return allocated;
    }

    void* TrampolineAllocate(const unsigned char* dst, size_t alloc_size)
    {
        FILE* fp = fopen("/proc/self/maps", "r");
        if(!fp) {
            EMOCK_REPORT_FAILURE("Failed to fetch current proc maps");
            return NULL;
        }

        while(!feof(fp)) {
            char buf[PATH_MAX + 100] = {0};
            if(fgets(buf, sizeof(buf), fp) == 0)
                break;

            unsigned long begin, end, last_end = 0;
            sscanf(buf, "%lx-%lx %*[^\n]", &begin, &end);
            if(last_end && begin != last_end && begin - last_end > alloc_size) {
                // alloc at end of last
                if((size_t)(dst - (unsigned char*)last_end) < kMaxAllocationDelta) {
                    if(void* allocated = TrampolineAllocateImpl(dst, alloc_size)) {
                        fclose(fp);
                        return allocated;
                    }
                }
                // alloc at begin of current
                if((size_t)((unsigned char*)begin - dst) < kMaxAllocationDelta) {
                    if(void* allocated = TrampolineAllocateImpl(dst - alloc_size, alloc_size)) {
                        fclose(fp);
                        return allocated;
                    }
                }
            }
            last_end = end;
        }

        fclose(fp);
        return NULL;
    }

    inline void TrampolineFree(unsigned char* allocated, size_t alloc_size)
    {
        munmap(allocated, alloc_size);
    }

#endif

    unsigned char* getTrampoline(const void* src, size_t alloc_size)
    {
        unsigned char* trampoline = NULL;
        for(std::list<TrampolineInfo>::iterator it = g_trampolines.begin();
            it != g_trampolines.end();
            ++it) {
            if(it->size - it->used > alloc_size) {
                trampoline = it->base + it->used;
                it->used += alloc_size;
                break;
            }
        }
        if(!trampoline) {
            TrampolineInfo info = {NULL, kAllocationSize, alloc_size};
            trampoline = info.base = (unsigned char*)TrampolineAllocate((const unsigned char*)src, info.size);
            g_trampolines.push_back(info);
        }
        return trampoline;
    }

}

#if BUILD_FOR_X64
    // FF 25 : JMP /4   jmp absolute indirect
    // bytes 2 ~ 5 : operand of jmp, relative to the memory that recorded the thunk addr. it should be zero.
    // bytes 6 ~ 13 : the absolute addr of thunk.
    static const unsigned char longJmpCodeTemplate[]  =
       { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#endif

    void* Trampoline::get(const void* src, void* dst) {
#if BUILD_FOR_X64
        if(std::abs((long)src - (long)dst) > kMaxAllocationDelta) {
            unsigned char* trampoline = getTrampoline(src, sizeof(longJmpCodeTemplate));
            ::memcpy(trampoline, longJmpCodeTemplate, sizeof(longJmpCodeTemplate));
            *(uintptr_t *)&trampoline[6] = (uintptr_t)dst;
            return trampoline;
        }
        else
            return dst;
#elif BUILD_FOR_X86
        return dst;
#endif
    }

    void* Trampoline::get4MemFunc(const void* src, void* dst) {
#ifdef _MSC_VER
        static const unsigned char ecxToArgList[] = { 0x58, 0x51, 0x50 };
        // apply trampoline and push ecx
    #if BUILD_FOR_X64
        unsigned char* trampoline = getTrampoline(src, sizeof(ecxToArgList) + sizeof(longJmpCodeTemplate));
        ::memcpy(trampoline, ecxToArgList, sizeof(ecxToArgList));
        ::memcpy(trampoline + sizeof(ecxToArgList), longJmpCodeTemplate, sizeof(longJmpCodeTemplate));
        *(uintptr_t *)&trampoline[sizeof(ecxToArgList) + 6] = (uintptr_t)dst;
    #elif BUILD_FOR_X86
        static const unsigned char x86JmpCodeTemplate[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
        unsigned char* trampoline = getTrampoline(src, sizeof(ecxToArgList) + sizeof(x86JmpCodeTemplate));
        ::memcpy(trampoline, ecxToArgList, sizeof(ecxToArgList));
        ::memcpy(trampoline + sizeof(ecxToArgList), x86JmpCodeTemplate, sizeof(x86JmpCodeTemplate));
        *(unsigned int*)&trampoline[sizeof(ecxToArgList) + 1] = (unsigned int)((unsigned long)dst - (unsigned long)trampoline - sizeof(x86JmpCodeTemplate) - sizeof(ecxToArgList));
    #endif
        return trampoline;

#else
        return get(src, dst);
#endif
    }

    void Trampoline::reset() {
        for(std::list<TrampolineInfo>::iterator it = g_trampolines.begin();
            it != g_trampolines.end();
            ++it) {
            TrampolineFree(it->base, it->size);
        }
        g_trampolines.clear();
    }

EMOCK_NS_END
