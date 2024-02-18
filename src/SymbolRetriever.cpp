/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
***/

#include <typeinfo>
#include <set>
#include <map>
#include <stack>

#include <emock/SymbolRetriever.h>
#include <emock/TypeString.h>
#include <emock/ReportFailure.h>

#if (_MSC_VER) ||  (__MINGW32__)

	#include <Windows.h>
	#include <DbgHelp.h>
    #include <vector>

    #pragma message("111111") 

    #ifdef _MSC_VER
	    #pragma comment(lib, "Dbghelp.lib")
    #endif

    #ifdef _WIN64 // [
        typedef unsigned __int64  uintptr_t;
    #else // _WIN64 ][
        typedef _W64 unsigned int uintptr_t;
    #endif // _WIN64 ]

#else

	#include <sys/mman.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <string.h>
	#include <unistd.h>
	#include <cassert>
	#include <stdio.h>
    #if __APPLE__
        #include <mach-o/dyld.h>
        #include <mach-o/dyld_images.h>
        #include <mach-o/fat.h>
        #include <mach-o/nlist.h>
        #include <dlfcn.h>
        #include <ar.h>
        #include <limits.h>
    #else
	    #include <link.h>
        #include <linux/limits.h>
    #endif

#endif

EMOCK_NS_START

    namespace {
        // MIT License
        // Copyright (c) 2010-2017 <http://ez8.co> <orca.zhang@yahoo.com>
        // https://gist.github.com/orca-zhang/fe6610c3d47299439a0fa118c925e29c
        bool MatchString(const char* src, const char* matcher)
        {
            std::stack<std::pair<const char*, const char*> > s;
            // scan from start
            while(*src) {
                // match asterisk
                if(*matcher == '*') {
                    // skip continuous asterisks
                    while(*matcher == '*' && ++matcher);
                    // forward to first match char of src
                    while(*src && *src != *matcher && ++src);
                    // record current position for back-track
                    s.push(std::make_pair(src + 1, matcher - 1));
                }
                // eat one character
                else if(*matcher == '?' || *src == *matcher) {
                    ++src, ++matcher;
                }
                // hit mismatch, then back-track
                else {
                    if(s.empty())
                        return false;
                    src = s.top().first, matcher = s.top().second;
                    s.pop();
                }
            }
            // ignore ending asterisks
            while(*matcher == '*' && ++matcher);
            return (!*src && !*matcher);
        }

        static std::string extractMethodName(const std::string& stringify) {
            size_t start = stringify.find_last_of(':') + 1;
            return stringify.substr(start, stringify.find_last_not_of(')') - start + 1);
        }

#if (_MSC_VER) ||  (__MINGW32__)
        static std::string extractMethodSignatureName(const char* pmf_info, std::string& symbolName, const std::string& stringify) {
#else
        static std::string extractMethodSignatureName(const char* pmf_info, const std::string& stringify) {
#endif
            const char* from = NULL;
            while(*pmf_info) {
                if(*pmf_info == '(')
                    from = pmf_info + 1;
                else if(*pmf_info == ')') {
                    std::string ret(from, pmf_info - from - 1);
                    ret += extractMethodName(stringify);
                    // extract symbol name
#if (_MSC_VER) ||  (__MINGW32__)
                    symbolName = strchr(ret.c_str(), ' ') + 1;
#endif
                    // extract arg list
                    int depth = 0;
                    from = (pmf_info = strchr(pmf_info + 1, '('));
                    while(*pmf_info) {
                        if(*pmf_info == '(')
                            ++depth;
                        else if(*pmf_info == ')')
                            if(!--depth) {
                                ret.append(from, pmf_info - from + 1);
                                if(std::string(pmf_info + 1) == " const") {
                                    ret += " const";
                                }
                                break;
                            }
                        ++pmf_info;
                    }
                    return ret;
                }
                ++pmf_info;
            }
            return ""; // impossible return
        }
    }

#if (_MSC_VER) ||  (__MINGW32__)

    std::map<std::pair<ULONG64, std::string>, std::map<int, std::string> > g_symbolCache;
    void SymbolRetriever::reset() {
        g_symbolCache.clear();
    }

    namespace {
        class DbgHelper
        {
        public:
            DbgHelper() {
                SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
                SymInitialize(GetCurrentProcess(), NULL, TRUE);
            }
            ~DbgHelper() {
                SymCleanup(GetCurrentProcess());
            }
        };

        static std::string toMangledPrefix(const char* symbolName) {
            std::string ret("?");
            std::vector<std::string> ns;
            const char* to = NULL;
            while((to = strstr(symbolName, "::"))) {
                ns.push_back(std::string(symbolName, to - symbolName));
                symbolName = to + 2;
            }
            ns.push_back(symbolName);
            for(size_t i = ns.size(); i > 0; --i) {
                ret += ns[i - 1];
                ret += '@';
            }
            ret += "@*";
            return ret;
        }

		DWORD64 getModBase(DWORD64 dwAddress) {
			IMAGEHLP_MODULE64 moduleInfo = { sizeof(IMAGEHLP_MODULE64) };
			if (SymGetModuleInfo64(GetCurrentProcess(), dwAddress, &moduleInfo)) {
				return moduleInfo.BaseOfImage;
			}
			return 0;
		}

        std::string getPdbPath(DWORD64 dwAddress) {
            IMAGEHLP_MODULE64 moduleInfo = { sizeof(IMAGEHLP_MODULE64) };
            if(SymGetModuleInfo64(GetCurrentProcess(), dwAddress, &moduleInfo)) {
				const char* p = (char*)&moduleInfo + offsetof(IMAGEHLP_MODULE64, LoadedImageName) + sizeof(moduleInfo.LoadedImageName);
                if(sizeof(IMAGEHLP_MODULE64) > offsetof(IMAGEHLP_MODULE64, LoadedImageName) + sizeof(moduleInfo.LoadedImageName) && *p) {
                    return p;
                }
                else {
                    char filePath[MAX_PATH] = {0};
                    /*
                    typedef enum {
                        sfImage = 0,
                        sfDbg,
                        sfPdb,
                        sfMpd,
                        sfMax
                    } IMAGEHLP_SF_TYPE;
                    */
                    if(SymGetSymbolFile(GetCurrentProcess(), NULL, moduleInfo.ImageName, 2/*sfDbg*/, filePath, MAX_PATH, filePath, MAX_PATH))
                        return filePath;
                }
            }
            return "";
        }

        static BOOL CALLBACK symbolsCallback(PSYMBOL_INFO pSymInfo, ULONG, PVOID UserContext) {
            ((std::set<ULONG64>*)UserContext)->insert(pSymInfo->Address);
            return TRUE;
        }

        static BOOL CALLBACK symbolsCallbackEx(PSYMBOL_INFO pSymInfo, ULONG, PVOID UserContext) {
            ((std::map<ULONG64, std::string>*)UserContext)->insert(std::make_pair(pSymInfo->Address, pSymInfo->Name));
            return TRUE;
        }

        void methodOffset(const std::string& pdbPath, const std::string& mangledPrefix, std::map<std::string, int>& offsets) {
            FILE* fp = fopen(pdbPath.c_str(), "rb");
            if (!fp)
                return;

            const size_t BUFFER_SIZE = 102400;
            char* buffer = new char[BUFFER_SIZE];
            char undecoratedName[MAX_PATH];

            while(!feof(fp)) {
                size_t bufLen = fread(buffer, 1, BUFFER_SIZE, fp);
                char* p = buffer;
                while(p < buffer + bufLen && (p = (char*)memchr(p, mangledPrefix[0], bufLen - (p - buffer)))) {
                    int offset = 0;
                    if(p - buffer > 6) {
                        offset = *(int*)(p - 6);
                    }
                    ++p;
                    size_t remain = bufLen - (p - buffer);
                    if(remain <= MAX_PATH) {
                        memmove(p, buffer, remain);
                        bufLen = fread(buffer + remain, 1, BUFFER_SIZE - remain, fp) + remain;
                        p = buffer;
                    }
                    if(MatchString(p, &mangledPrefix[1])) {
                        if(UnDecorateSymbolName(p - 1, undecoratedName, MAX_PATH,
                                           UNDNAME_NO_MEMBER_TYPE | 
                                           UNDNAME_NO_ACCESS_SPECIFIERS | 
                                           UNDNAME_NO_FUNCTION_RETURNS | 
                                           UNDNAME_NO_THISTYPE)) {
                            offsets[undecoratedName] = offset;
                        }
                        p += strlen(p);
                    }
                    else
                        ++p;
                }
            }

            delete [] buffer;
            fclose(fp);
        }
    }

    void* SymbolRetriever::getMethodAddress(void* p, const std::type_info& info, const std::string& stringify) {
        DbgHelper dbgHelper;
        std::string symbolName;
        std::string signature = extractMethodSignatureName(info.name(), symbolName, stringify);
		std::set<ULONG64> v;
		ULONG64 modBase = getModBase((DWORD64)p);
        SymEnumSymbols(GetCurrentProcess(), modBase, modBase > 0 ? symbolName.c_str() : std::string("*!").append(symbolName).c_str(), symbolsCallback, &v);
        if(v.empty()) {
            EMOCK_REPORT_FAILURE(std::string("Failed to find symbol of [").append(stringify).append("], maybe inlined or not impleted in derived class.").c_str());
            return NULL;
        }
		std::set<ULONG64>::const_iterator itRet = v.begin();
        if(v.size() == 1)
            return (void*)*itRet;
        std::map<int, std::string>& offsets = g_symbolCache[std::make_pair(modBase, symbolName)];
        std::map<int, std::string>::const_iterator it;
        if(offsets.empty()) {
			std::string pdbPath = getPdbPath(*itRet);
            if(pdbPath.empty()) {
                EMOCK_REPORT_FAILURE(std::string("Failed to find pdbfile of [").append(stringify).append("]").c_str());
                return NULL;
            }
            std::map<std::string, int> offsetsAux;
            methodOffset(pdbPath, toMangledPrefix(symbolName.c_str()), offsetsAux);
            for(std::map<std::string, int>::const_iterator i = offsetsAux.begin(); i != offsetsAux.end(); ++i)
                offsets[i->second] = i->first;
        }
        if(offsets.size() != v.size()) {
            EMOCK_REPORT_FAILURE(std::string("Symbol size that from 'pdbfile' and 'SymEnumSymbols' API not equal of [").append(stringify).append("]").c_str());
            return NULL;
        }
        for(it = offsets.begin(); it != offsets.end(); ++it, ++itRet) {
            if(it->second == signature)
                return (void*)*itRet;
        }
        EMOCK_REPORT_FAILURE(std::string("Failed to get address of [").append(stringify).append("]").c_str());
        return NULL;
    }

    void* SymbolRetriever::getAddress(std::string& name, const std::string& matcher) {
        DbgHelper dbgHelper;
        size_t pos = matcher.find('@');
        std::string libMatcher((pos == std::string::npos) ? "*" : matcher.substr(pos + 1));
        std::string symMatcherWithoutLib((pos == std::string::npos) ? matcher : matcher.substr(0, pos));
        size_t argPos = symMatcherWithoutLib.find('(');
        std::string symMatcher(argPos == std::string::npos ? symMatcherWithoutLib : symMatcherWithoutLib.substr(0, argPos));
        std::string enumMask(std::string(libMatcher).append("!").append(symMatcher));
        std::map<ULONG64, std::string> m;
        SymEnumSymbols(GetCurrentProcess(), 0, enumMask.c_str(), symbolsCallbackEx, &m);
        if(!m.empty()) {
            std::map<ULONG64, std::string>::iterator itRet = m.begin();
            std::map<int, std::string>& offsets = g_symbolCache[std::make_pair(0, enumMask)];
            std::map<int, std::string>::const_iterator it;
            if(offsets.empty()) {
                std::string pdbPath = getPdbPath((DWORD64)itRet->first);
                if(pdbPath.empty()) {
                    EMOCK_REPORT_FAILURE(std::string("Failed to find pdbfile of [").append(enumMask).append("]").c_str());
                    return NULL;
                }
                std::map<std::string, int> offsetsAux;
                methodOffset(pdbPath, toMangledPrefix(symMatcher.c_str()), offsetsAux);
                for(std::map<std::string, int>::const_iterator i = offsetsAux.begin(); i != offsetsAux.end(); ++i)
                    offsets[i->second] = i->first;
            }
			if (offsets.size() != m.size()) {
				EMOCK_REPORT_FAILURE(std::string("Symbol size that from 'pdbfile' and 'SymEnumSymbols' API not equal of [").append(enumMask).append("]").c_str());
				return NULL;
			}
            // arglist: () -> (void)
            if(symMatcherWithoutLib[argPos + 1] == ')') {
                symMatcherWithoutLib.insert(argPos + 1, "void");
            }
            for(it = offsets.begin(); it != offsets.end(); ++it) {
                // remove mismatch ones
                if(!MatchString(it->second.c_str(), std::string("__thiscall ")
													.append(symMatcherWithoutLib)
													.append(argPos == std::string::npos ? "(*)" : "")
													.c_str())) {
                    m.erase(itRet++);
                }
                else {
                    itRet->second = it->second;
                    ++itRet;
                }
            }
            if(m.size() == 1) {
				itRet = m.begin();
                name = itRet->second;
                return (void*)itRet->first;
            }
            std::string info("Failed to get address of [");
            info.append(matcher).append("]. candidates:\n");
            for(itRet = m.begin(); itRet != m.end(); ++itRet) {
                info.append("\t").append(itRet->second).append("\n");
            }
            EMOCK_REPORT_FAILURE(info.c_str());
        }
        else {
            EMOCK_REPORT_FAILURE(std::string("Failed to get address of [").append(matcher).append("], maybe inlined or haven't been overridden in derived class.").c_str());
        }
        return NULL;
    }

#else

    void SymbolRetriever::reset() {}

    namespace {
        struct ISymbolCheckor
        {
            virtual void setDlBase(unsigned long long dlBase) = 0;
            virtual bool libCheck(const char* name) const = 0;
            virtual bool libContinue() const = 0;
            virtual bool symContinue(const char* name, unsigned long long addr) = 0;
        };

        struct SymbolEqual : public ISymbolCheckor
        {
            SymbolEqual(const std::string& signature)
                : _signature(signature)
                , _addr(0)
                , _dlBase(0) {
            }
            void setDlBase(unsigned long long dlBase) {
                _dlBase = dlBase;
            }
            inline bool libCheck(const char* name) const {
                return true;
            }
            inline bool libContinue() const {
                return !_addr;
            }
            inline bool symContinue(const char* name, unsigned long long addr) {
                if(name == _signature) {
                    _addr = _dlBase + addr;
                    return false;
                }
                return true;
            }
            unsigned long long getAddr() const {
                return _addr;
            }

        private:
            std::string _signature;
            unsigned long long _addr;
            unsigned long long _dlBase;
        };

        struct SymbolMatcher : public ISymbolCheckor
        {
            SymbolMatcher(const std::string& libMatcher,
                          const std::string& symMatcher,
                          std::map<unsigned long long, std::string>& symMap)
                : _libMatcher(libMatcher)
                , _symMatcher(symMatcher)
                , _dlBase(0)
                , _symMap(symMap) {
            }
            void setDlBase(unsigned long long dlBase) {
                _dlBase = dlBase;
            }
            inline bool libCheck(const char* name) const {
                return MatchString(name, _libMatcher.c_str());
            }
            inline bool libContinue() const {
                return true;
            }
            bool symContinue(const char* name, unsigned long long addr) {
                if(MatchString(name, _symMatcher.c_str())) {
                    _symMap.insert(std::make_pair(_dlBase + addr, name));
                }
                return true;
            }

        private:
            std::string _libMatcher;
            std::string _symMatcher;
            unsigned long long _dlBase;
            std::map<unsigned long long, std::string>& _symMap;
        };

    #if !__APPLE__
        template<typename Elf_Ehdr, typename Elf_Shdr, typename Elf_Sym>
        bool _findAddr(const char* base, ISymbolCheckor* checkor)
        {
            const Elf_Ehdr* elf_header = (const Elf_Ehdr*)base;
            const Elf_Shdr* elf_section = (const Elf_Shdr*)(base + elf_header->e_shoff);
            for(int i = 0; i < elf_header->e_shnum; ++i) {
                if(elf_section[i].sh_type != SHT_SYMTAB) {
                    continue;
                }
                const char* strTab = (const char*)(base + elf_section[elf_section[i].sh_link].sh_offset);
                const Elf_Sym* symTable = (const Elf_Sym*)(base + elf_section[i].sh_offset);
                for(unsigned int j = 0; j < elf_section[i].sh_size / elf_section[i].sh_entsize; ++j) {
                    if(ELF32_ST_TYPE(symTable[j].st_info) != STT_FUNC || !symTable[j].st_value || symTable[j].st_shndx == SHN_UNDEF)
                        continue;
                    const char* symClsName = strTab + symTable[j].st_name;
                    const char* outterLib = strchr(symClsName, '@');
                    if(!checkor->symContinue(getDemangledName(outterLib ? std::string(symClsName, outterLib - symClsName).c_str() : symClsName).c_str(),
                                                symTable[j].st_value))
                        return true;
                }
            }
            return false;
        }
    #endif

        bool findAddrInElf(const char* file_name, ISymbolCheckor* checkor) {
            bool ret = false;
            int fd = -1;
            if((fd = open(file_name, O_RDONLY)) > 0) {
                struct stat sb;
                if(!fstat(fd, &sb)) {
                    char* base = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
                    if(base != MAP_FAILED) {
    #if __APPLE__
                        switch (*(uint32_t*)base) {
                        case FAT_MAGIC:
                        case FAT_CIGAM:
                        case FAT_MAGIC_64:
                        case FAT_CIGAM_64:
                            break;

                        case MH_MAGIC:
                        case MH_CIGAM:
                            {
                                mach_header *header = (mach_header *)base;
                                load_command * lc = (load_command *)(base + sizeof(*header));
                                for (int i=0; i<header->ncmds; ++i) {
                                    if (lc->cmd == LC_SYMTAB) {
                                        symtab_command * symc = (struct symtab_command *)lc;
                                        char * strtab = (char *)base + symc->stroff;
                                        struct nlist * symtab = (struct nlist *)((char*)base + symc->symoff);
                                        for (int j=0; j < symc->nsyms; ++j) {
                                            const char* symClsName = strtab + ((struct nlist*)&symtab[j])->n_un.n_strx;
                                            const char* outterLib = strchr(symClsName, '@');
                                            if(!checkor->symContinue(getDemangledName(outterLib ? std::string(symClsName, outterLib - symClsName).c_str() : symClsName).c_str(),
                                                                    (uintptr_t)((struct nlist*)&symtab[j])->n_value))
                                                return true;
                                        }
                                    }
                                    lc = (struct load_command *)((uint8_t *)lc + lc->cmdsize);
                                }
                            }
                            break;

                        case MH_MAGIC_64:
                        case MH_CIGAM_64:
                            {
                                mach_header_64 *header = (mach_header_64 *)base;
                                load_command * lc = (load_command *)(base + sizeof(*header));
                                for (int i=0; i<header->ncmds; ++i) {
                                    if (lc->cmd == LC_SYMTAB) {
                                        symtab_command * symc = (struct symtab_command *)lc;
                                        char * strtab = (char *)base + symc->stroff;
                                        struct nlist_64 * symtab = (struct nlist_64 *)((char*)base + symc->symoff);
                                        for (int j=0; j < symc->nsyms; ++j) {
                                            const char* symClsName = strtab + ((struct nlist_64*)&symtab[j])->n_un.n_strx;
                                            const char* outterLib = strchr(symClsName, '@');
                                            if(!checkor->symContinue(getDemangledName(outterLib ? std::string(symClsName, outterLib - symClsName).c_str() : symClsName).c_str(),
                                                                    (uintptr_t)((struct nlist_64*)&symtab[j])->n_value))
                                                return true;
                                        }
                                    }
                                    lc = (struct load_command *)((uint8_t *)lc + lc->cmdsize);
                                }
                            }
                            break;

                        //case FT_ARMAG:
                        //    break;

                        default:
                            break;
                        }

    #else
                        switch(base[EI_CLASS]) {
                            case 1:
                              ret = _findAddr<Elf32_Ehdr, Elf32_Shdr, Elf32_Sym>(base, checkor);
                              break;
                            case 2:
                              ret = _findAddr<Elf64_Ehdr, Elf64_Shdr, Elf64_Sym>(base, checkor);
                              break;
                        }
    #endif
                        munmap(base, sb.st_size);
                    }
                }
                close(fd);
            }
            return ret;
        }
    }

    void symbolRetrieve(ISymbolCheckor* checkor) {
        char file_name[PATH_MAX] = {0};
    #if __APPLE__
        uint32_t size = PATH_MAX;
        if(_NSGetExecutablePath(&file_name[0], &size) != -1) {
    #else
        if(readlink("/proc/self/exe", file_name, PATH_MAX) > 0) {
    #endif
            if(findAddrInElf(file_name, checkor)) {
                if(checkor->libContinue() == false)
                    return;
            }
        }

    #if __APPLE__
        task_dyld_info dyld_info;
        mach_msg_type_number_t count = TASK_DYLD_INFO_COUNT;
        if (task_info(mach_task_self(), TASK_DYLD_INFO, (task_info_t)&dyld_info, &count)) {
            return;
        }

        // Get image array's size and address
        dyld_all_image_infos *infos = (dyld_all_image_infos *)dyld_info.all_image_info_addr;
        for (int i = 0; i < infos->infoArrayCount; ++i) {
            const dyld_image_info *image = infos->infoArray + i;
            if(checkor->libCheck(image->imageFilePath)) {
                if(findAddrInElf(image->imageFilePath, checkor)) {
                    if(checkor->libContinue() == false) {
                        checkor->setDlBase((unsigned long long)image->imageLoadAddress);
                        break;
                    }
                }
            }
        }
    #else
        FILE* fp = fopen("/proc/self/maps", "r");
        if(!fp) {
            EMOCK_REPORT_FAILURE(std::string("Failed to fetch current proc maps of [").append(file_name).append("]").c_str());
            return;
        }
        std::set<std::string> aux_set;
        aux_set.insert(file_name);
        while(!feof(fp)) {
            char buf[PATH_MAX + 100] = {0};
            if(fgets(buf, sizeof(buf), fp) == 0)
                break;

            unsigned long begin;
            sscanf(buf, "%lx-%*[^ ] %*[^ ] %*[^ ] %*[^ ] %*[^ ] %s", &begin, file_name);
            if(aux_set.count(file_name) == 0) {
                Dl_info dlinfo;
                if(dladdr((void*)begin, &dlinfo)) {
                    if(checkor->libCheck(dlinfo.dli_fname)) {
                        checkor->setDlBase((unsigned long long)dlinfo.dli_fbase);
                        if(findAddrInElf(dlinfo.dli_fname, checkor)) {
                            if(checkor->libContinue() == false)
                                break;
                        }
                    }
                }
                aux_set.insert(file_name);
            }
        }
        fclose(fp);
    #endif
    }

    void* SymbolRetriever::getMethodAddress(void*, const std::type_info& info, const std::string& stringify) {
        std::string signature = extractMethodSignatureName(getDemangledName(info.name()).c_str(), stringify);
        SymbolEqual se(signature);
        symbolRetrieve(&se);
        if(se.getAddr()) {
            return (void*)se.getAddr();
        }
        EMOCK_REPORT_FAILURE(std::string("Failed to get address of [").append(stringify).append("], maybe inlined or haven't been overridden in derived class.").c_str());
        return NULL;
    }

    void* SymbolRetriever::getAddress(std::string& name, const std::string& matcher) {
        size_t pos = matcher.find('@');
        std::string libMatcher((pos == std::string::npos) ? "*" : matcher.substr(pos + 1));
        std::string symMatcherWithoutLib((pos == std::string::npos) ? matcher : matcher.substr(0, pos));
        std::string symMatcher(symMatcherWithoutLib.find('(') == std::string::npos ? symMatcherWithoutLib + "(*)" : symMatcherWithoutLib);
        std::map<unsigned long long, std::string> symMap;
        SymbolMatcher sm(libMatcher, symMatcher, symMap);
        symbolRetrieve(&sm);
        if(!symMap.empty()) {
            if(symMap.size() == 1) {
                name = symMap.begin()->second;
                return (void*)symMap.begin()->first;
            }
            std::string info("Failed to get address of [");
            info.append(matcher).append("]. candidates:\n");
            for(std::map<unsigned long long, std::string>::const_iterator it = symMap.begin();
                it != symMap.end();
                ++it) {
                info.append("\t").append(it->second).append("\n");
            }
            EMOCK_REPORT_FAILURE(info.c_str());
        }
        else {
            EMOCK_REPORT_FAILURE(std::string("Failed to get address of [").append(matcher).append("], maybe inlined or haven't been overridden in derived class.").c_str());
        }
        return NULL;
    }

#endif

EMOCK_NS_END
