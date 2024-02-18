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

#if (_MSC_VER) ||  (__MINGW32__)

    #include <Windows.h>
	#include <cassert>
    #ifdef _WIN64 // [
        typedef unsigned __int64  uintptr_t;
    #else // _WIN64 ][
        typedef _W64 unsigned int uintptr_t;
    #endif // _WIN64 ]
    typedef signed __int64     int64_t;

#else

    #include <sys/mman.h>
    #include <inttypes.h>
    #include <stdio.h>

    #if __APPLE__
        #include <limits.h>
        #include <mach/mach_vm.h>
        #include <mach/mach_init.h>
    #else
        #include <linux/limits.h>

    #endif

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

#define EMOCK_PAGE_ALIGN_BITS  12
#define EMOCK_PAGE_SIZE        (1 << EMOCK_PAGE_ALIGN_BITS)

static const size_t kMaxAllocationDelta = 0x80000000; // 2GB
static const size_t kAllocationSize     = EMOCK_PAGE_SIZE;  // 4KB
static const size_t kAlignmentSize      = 64;         // 64

#if (_MSC_VER) ||  (__MINGW32__)

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

            if ((uintptr_t)mbi.AllocationBase + mbi.RegionSize > _ADDRESS_MAX_VALUE)
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
            if (std::abs((int64_t)dst - (int64_t)allocated) > kMaxAllocationDelta)
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

    #define ALIGN_TO_PAGE_BOUNDARY(addr) (void*) (((uintptr_t)addr) >> EMOCK_PAGE_ALIGN_BITS << EMOCK_PAGE_ALIGN_BITS)

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
    #if __APPLE__
        uintptr_t last_end = 0;
        while(true) {
            mach_vm_address_t address = last_end;
            mach_vm_size_t size = 0;
            uint32_t depth = 2048;
            vm_region_submap_info_data_64_t info;
            mach_msg_type_number_t count = VM_REGION_SUBMAP_INFO_COUNT_64;
            kern_return_t kr = mach_vm_region_recurse(mach_task_self(), &address, &size,
                                                    &depth, (vm_region_recurse_info_t)&info, &count);
            if (kr != KERN_SUCCESS) {
                break;
            }

            // first block is too far
            if(std::abs((int64_t)address - (int64_t)dst) > kMaxAllocationDelta) {
                for (size_t i = 0; i < 10000; i++) {
                    uintptr_t begin = floor((double)(kMaxAllocationDelta - alloc_size) / kAllocationSize - i) * kAllocationSize;
                    if(void* allocated = TrampolineAllocateImpl((unsigned char*)begin, alloc_size)) {
                        return allocated;
                    }
                }
                break;
            }

            uintptr_t begin = address;
            uintptr_t end = address + size;
            if(last_end && begin != last_end && begin - last_end > alloc_size) {
                // alloc at end of last
                if(std::abs((int64_t)dst - (int64_t)last_end) < kMaxAllocationDelta) {
                    // last_end align forward
                    last_end = ceil((double)last_end / kAllocationSize) * kAllocationSize;
                    if(void* allocated = TrampolineAllocateImpl((unsigned char*)last_end, alloc_size)) {
                        return allocated;
                    }
                }
                // alloc at begin of current
                if(std::abs((int64_t)begin - (int64_t)dst) < kMaxAllocationDelta) {
                    // begin align backward
                    begin = floor((double)(begin - alloc_size) / kAllocationSize) * kAllocationSize;
                    if(void* allocated = TrampolineAllocateImpl((unsigned char*)begin - alloc_size, alloc_size)) {
                        return allocated;
                    }
                }
            }
            last_end = end;
        }
        if(void* allocated = TrampolineAllocateImpl(dst - alloc_size, alloc_size)) {
            return allocated;
        }
    #else
        FILE* fp = fopen("/proc/self/maps", "r");
        if(!fp) {
            EMOCK_REPORT_FAILURE("Failed to fetch current proc maps");
            return NULL;
        }

        uintptr_t last_end = 0;
        while(!feof(fp)) {
            char buf[PATH_MAX + 100] = {0};
            if(fgets(buf, sizeof(buf), fp) == 0)
                break;

            uintptr_t begin, end = 0;
            sscanf(buf, "%lx-%lx %*[^\n]", &begin, &end);
            if(last_end && begin != last_end && begin - last_end > alloc_size) {
                // alloc at end of last
                if(std::abs((int64_t)dst - (int64_t)last_end) < kMaxAllocationDelta) {
                    // last_end align forward
                    last_end = ceil((double)last_end / kAllocationSize) * kAllocationSize;
                    if(void* allocated = TrampolineAllocateImpl((unsigned char*)last_end, alloc_size)) {
                        fclose(fp);
                        return allocated;
                    }
                }
                // alloc at begin of current
                if(std::abs((int64_t)begin - (int64_t)dst) < kMaxAllocationDelta) {
                    // begin align backward
                    begin = floor((double)(begin - alloc_size) / kAllocationSize) * kAllocationSize;
                    if(void* allocated = TrampolineAllocateImpl((unsigned char*)begin - alloc_size, alloc_size)) {
                        fclose(fp);
                        return allocated;
                    }
                }
            }
            last_end = end;
        }

        fclose(fp);
    #endif
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
            if(it->size - it->used > ceil((double)alloc_size / kAlignmentSize) * kAlignmentSize) {
                trampoline = it->base + it->used;
                it->used += size_t(ceil((double)alloc_size / kAlignmentSize) * kAlignmentSize);
                break;
            }
        }
        if(!trampoline) {
            TrampolineInfo info = {NULL, kAllocationSize, (size_t)ceil((double)alloc_size / kAlignmentSize) * kAlignmentSize};
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
        if(std::abs((int64_t)src - (int64_t)dst) > kMaxAllocationDelta) {
            unsigned char* trampoline = getTrampoline(src, sizeof(longJmpCodeTemplate));
            if(!trampoline) {
                return NULL;
            }
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
#if (_MSC_VER) ||  (__MINGW32__)
        static const unsigned char ecxToArgList[] = { 0x58, 0x51, 0x50 };
        // apply trampoline and push ecx
    #if BUILD_FOR_X64
        unsigned char* trampoline = getTrampoline(src, sizeof(ecxToArgList) + sizeof(longJmpCodeTemplate));
        if(!trampoline) {
            return NULL;
        }
        ::memcpy(trampoline, ecxToArgList, sizeof(ecxToArgList));
        ::memcpy(trampoline + sizeof(ecxToArgList), longJmpCodeTemplate, sizeof(longJmpCodeTemplate));
        *(uintptr_t *)&trampoline[sizeof(ecxToArgList) + 6] = (uintptr_t)dst;
    #elif BUILD_FOR_X86
        static const unsigned char x86JmpCodeTemplate[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
        unsigned char* trampoline = getTrampoline(src, sizeof(ecxToArgList) + sizeof(x86JmpCodeTemplate));
        if(!trampoline) {
            return NULL;
        }
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
