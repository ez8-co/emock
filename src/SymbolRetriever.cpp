/***
   mockcpp is a C/C++ mock framework.
   Copyright (c) 2010-2017 <http://ez8.co> <orca.zhang@yahoo.com>

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

#include <typeinfo>

#include <mockcpp/SymbolRetriever.h>
#include <mockcpp/TypeString.h>

#ifdef _MSC_VER

	#include <windows.h>
	#include <dbghelp.h>
	#include <vector>
    #include <map>
    #include <algorithm>
	#pragma comment(lib, "Dbghelp.lib")

#else

	#include <sys/mman.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <link.h>
	#include <string.h>
	#include <unistd.h>
	#include <cassert>
	#include <stdio.h>
    #include <linux/limits.h>
    #include <set>

#endif

MOCKCPP_NS_START

    namespace {
        static std::string extractMethodName(const std::string& stringify) {
            size_t start = stringify.find_last_of(':') + 1;
            return stringify.substr(start, stringify.find_last_not_of(')') - start + 1);
        }

#ifdef _MSC_VER
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
#ifdef _MSC_VER
                    symbolName = strstr(ret.c_str(), " ") + 1;
#endif
                    // extract arg list
                    int depth = 0;
                    from = (pmf_info = strchr(pmf_info + 1, '('));
                    while(*pmf_info) {
                        if(*pmf_info == '(')
                            ++depth;
                        else if(*pmf_info == ')')
                            if (!--depth) {
                               ret.append(from, pmf_info - from + 1);
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

#ifdef _MSC_VER

    std::map<std::string, std::vector<std::pair<int, std::string> > > kCache;
    void SymbolRetriever::reset() {
        kCache.clear();
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
            ret += "@";
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
                    if(SymGetSymbolFile(GetCurrentProcess(), NULL, moduleInfo.ImageName, sfPdb, filePath, MAX_PATH, filePath, MAX_PATH))
                        return filePath;
                }
            }
            return "";
        }

        static BOOL CALLBACK symbolsCallback(PSYMBOL_INFO pSymInfo, ULONG, PVOID UserContext) {
            ((std::vector<ULONG64>*)UserContext)->push_back(pSymInfo->Address);
            return TRUE;
        }

        int methodOffset(const std::string& pdbPath, const std::string& mangledPrefix, const std::string& methodSginature, std::vector<std::pair<int, std::string> >& offsets) {
            int ret = 0;
            FILE* fp = fopen(pdbPath.c_str(), "rb");
            if (!fp)
                return ret;

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
                    if(memcmp(&mangledPrefix[1], p, mangledPrefix.size() - 1) == 0) {
                        if(UnDecorateSymbolName(p - 1, undecoratedName, MAX_PATH,
                                           UNDNAME_NO_MEMBER_TYPE | 
                                           UNDNAME_NO_ACCESS_SPECIFIERS | 
                                           UNDNAME_NO_FUNCTION_RETURNS | 
                                           UNDNAME_NO_THISTYPE)) {
                            if (methodSginature == undecoratedName)
                                ret = offset;
                        }
                        offsets.push_back(std::make_pair(offset, undecoratedName));
                        p += mangledPrefix.size() - 1;
                        p += strlen(p);
                    }
                    else
                        p += mangledPrefix.size() - 1;
                }
            }

            delete [] buffer;
            fclose(fp);
            return ret;
        }
    }

    bool offsetCmp(const std::pair<int, std::string>& lhs, const std::pair<int, std::string>& rhs) {
        return lhs.first < rhs.first;
    }

    void* SymbolRetriever::getAddress(void* p, const std::type_info& info, const std::string& stringify) {
        DbgHelper dbgHelper;
        std::string symbolName;
        std::string signature = extractMethodSignatureName(info.name(), symbolName, stringify);
		std::vector<ULONG64> v;
		ULONG64 modBase = getModBase((DWORD64)p);
        SymEnumSymbols(GetCurrentProcess(), modBase, modBase > 0 ? symbolName.c_str() : std::string("*!").append(symbolName).c_str(), symbolsCallback, &v);
        if(v.empty())
            return NULL;
        if(v.size() == 1)
            return (void*)v[0];
        sort(v.begin(), v.end());
        std::vector<std::pair<int, std::string> >& offsets = kCache[symbolName];
        std::vector<std::pair<int, std::string> >::iterator it;
        if(!offsets.empty()) {
            for(it = offsets.begin(); it != offsets.end(); ++it) {
                if(it->second == signature)
                    break;
            }
        }
        else {
			std::string pdbPath = getPdbPath(v[0]);
            int offset = methodOffset(pdbPath, toMangledPrefix(symbolName.c_str()), signature, offsets);
            sort(offsets.begin(), offsets.end(), offsetCmp);
            for(it = offsets.begin(); it != offsets.end(); ++it) {
                if(it->first == offset)
                    break;
            }
        }
        return (it != offsets.end()) ? (void*)v[it - offsets.begin()] : NULL;
    }

#else
    void SymbolRetriever::reset() {}

    namespace {
        template<typename Elf_Ehdr, typename Elf_Shdr, typename Elf_Sym>
        unsigned long long _findAddr(const char* base, const std::string& signature)
        {
            const Elf_Ehdr* elf_header = (const Elf_Ehdr*)base;
            const Elf_Shdr* elf_section = (const Elf_Shdr*)(base + elf_header->e_shoff);
            const char* symTable = base + elf_section[elf_header->e_shnum - 1].sh_offset;
            for(int i = 1; i < elf_header->e_shnum; ++i) {
                if(strstr(base + elf_section[elf_header->e_shstrndx].sh_offset + elf_section[i].sh_name, "sym")) {
                    int symEntries = elf_section[i].sh_size / sizeof(Elf_Sym);
                    const Elf_Sym* symAddr = (const Elf_Sym*)(base + elf_section[i].sh_offset);
                    for(int j = 0; j < symEntries; ++j) {
                        if(ELF32_ST_TYPE(symAddr[j].st_info) != 2 || !symAddr[j].st_value)
                            continue;
                        const char* symClsName = symTable + symAddr[j].st_name;
                        const char* outterLib = strchr(symClsName, '@');
                        if(getDemangledName(outterLib ? std::string(symClsName, outterLib - symClsName).c_str() : symClsName)
                                        == signature) {
                            return symAddr[j].st_value;
                        }
                    }
                }
            }
            return 0;
        }


        unsigned long long findAddrInElf(const char* file_name, const std::string& signature) {
            unsigned long long ret = 0;
            int fd = -1;
            if((fd = open(file_name, O_RDONLY)) > 0) {
                struct stat sb;
                if(!fstat(fd, &sb)) {
                    char* base = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
                    if(base != MAP_FAILED) {
                        switch(base[EI_CLASS]) {
                            case 1:
                              ret = _findAddr<Elf32_Ehdr, Elf32_Shdr, Elf32_Sym>(base, signature);
                              break;
                            case 2:
                              ret = _findAddr<Elf64_Ehdr, Elf64_Shdr, Elf64_Sym>(base, signature);
                              break;
                        }
                        munmap(base, sb.st_size);
                    }
                }
                close(fd);
            }
            return ret;
        }
    }

    void* SymbolRetriever::getAddress(void*, const std::type_info& info, const std::string& stringify) {
        std::string signature = extractMethodSignatureName(getDemangledName(info.name()).c_str(), stringify);
        std::set<std::string> aux_set;
        unsigned long long ret = 0;
        char file_name[PATH_MAX] = {0};
        if(readlink("/proc/self/exe", file_name, PATH_MAX) > 0 && ((ret = findAddrInElf(file_name, signature)) > 0))
            return (void*)ret;

        aux_set.insert(file_name);
        FILE *f = fopen("/proc/self/maps", "r");
        if(!f)
            return NULL;

        while(!feof(f)) {
            char buf[PATH_MAX + 100] = {0};
            if(fgets(buf, sizeof(buf), f) == 0)
                break;

            unsigned long begin;
            sscanf(buf, "%lx-%*[^ ] %*[^ ] %*[^ ] %*[^ ] %*[^ ] %s", &begin, file_name);
            if(aux_set.count(file_name) == 0) {
                Dl_info dlinfo;
                if(dladdr((void*)begin, &dlinfo) && ((ret = findAddrInElf(dlinfo.dli_fname, signature)) > 0)) {
                    fclose(f);
                    return (void*)((long)dlinfo.dli_fbase + ret);
                }
                aux_set.insert(file_name);
            }
        }
        fclose(f);
        return NULL;
    }

#endif

MOCKCPP_NS_END
