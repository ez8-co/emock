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

#include <typeinfo>

#include <mockcpp/VirtualTable.h>
#include <mockcpp/ReportFailure.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/MethodInfoReader.h>
#include <mockcpp/ObjNameGetter.h>
#include <mockcpp/VirtualTableUtils.h>
#include <mockcpp/TypeString.h>


MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////
namespace
{
   struct FakeObject
   {
      void* vptr[MOCKCPP_MAX_INHERITANCE+1];
   };
}

/////////////////////////////////////////////////////////////////
struct VirtualTableImpl
{
	VirtualTableImpl( IndexInvokableGetter* getter
                   , ObjectNameGetter* nameGetter
                   , unsigned int numberOfVptr
                   , const std::type_info& info);
   ~VirtualTableImpl();

   void validateNumberOfVptr();
   void validateIndexOfVtbl(unsigned int index);
   void validateIndexOfVptr(unsigned int index);
   void validateVptr(void** vptr);

   void reset();

   FakeObject* fakeObject;
   void** vtbl;
   unsigned int numberOfVptr;
   IndexInvokableGetter* indexInvokableGetter;
   ObjectNameGetter* nameGetter;
   bool expectsBeingDeleted;
   bool expectsKeepAlive;
   bool deleted;
};


/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateVptr(void** pVptr)
{
   if(pVptr != fakeObject->vptr)
   {
      MOCKCPP_REPORT_FAILURE( PACKAGE " internal error(1018). please report this bug to "
             PACKAGE_BUGREPORT ".");
   }
}
/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateNumberOfVptr()
{
   if(numberOfVptr > MOCKCPP_MAX_INHERITANCE)
   {
      oss_t oss;

      oss << "Seems that the interface you are trying to mock "
          << "inherites from too many base classes (" 
          << numberOfVptr 
          << "), or it's not a pure virtual class. "
          << "Here are some hints for you: \n"
          << "1. " PACKAGE " only supports mocking pure virtual class; \n"
          << "2. you can change the MOCKCPP_MAX_INHERITANCE setting to "
             "maximun 7, then rebuild " PACKAGE "; \n"
          << "3. you can refine your design to make it simpler.";

      MOCKCPP_REPORT_FAILURE(oss.str());
   }
}
/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateIndexOfVtbl(unsigned int index)
{
   oss_t oss;

   oss << "Did you define too many methods in an interface? "
       << "Probably you should refine your design, "
       << "or you can reconfig MOCKCPP_MAX_VTBL_SIZE bigger, "
       << "it's current setting is " 
       << MOCKCPP_MAX_VTBL_SIZE 
       << ", the biggest value it could be set is 50. "
       << "FYI: the index of method which you are trying to mock is "
       << index + 1 << ".";

   MOCKCPP_ASSERT_TRUE(
      oss.str(), 
      index < MOCKCPP_MAX_VTBL_SIZE);
}

/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateIndexOfVptr(unsigned int index)
{
   if(index >= numberOfVptr)
   {
      MOCKCPP_REPORT_FAILURE(PACKAGE " internal error. please report it to " PACKAGE_BUGREPORT ".");
   }
}

/////////////////////////////////////////////////////////////////
namespace
{
   VirtualTableImpl*
   getVirtualTableImpl(void* caller, unsigned int vptrIndex)
   {
      void** vptr = &((void**)caller)[-(int)vptrIndex];
      VirtualTableImpl* pThis = (VirtualTableImpl*)vptr[MOCKCPP_MAX_INHERITANCE];
      pThis->validateVptr(vptr);
      return pThis;
   }

   struct MethodHolderDummy {};

   template <int VPTRIndex, int VTBLIndex, typename T>
   struct DefaultMethodHolder
   {
      void method()
      {
         VirtualTableImpl* pThis = getVirtualTableImpl((void*)this, VPTRIndex);

         oss_t oss;
         oss << "The method you are invoking is not " 
             << "specified by mocker" 
             << " ("
             << pThis->nameGetter->getName()
             << "["
             << VPTRIndex << ":" 
             << VTBLIndex << "])." ;



         MOCKCPP_REPORT_FAILURE(oss.str());
      }
   };
}

/////////////////////////////////////////////////////////////////
#define MOCKCPP_SET_DEFAULT_METHOD(I, J) do {\
   if(numberOfVptr > I) \
   { \
     vtbl[getRealVtblIndex(I, J)] = getAddrOfMethod(&DefaultMethodHolder<I, J, MethodHolderDummy>::method); \
   } \
}while(0)

/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::reset()
{
   #include <mockcpp/DefaultMethodAddrGetterDef.h>

   expectsBeingDeleted = false;
   expectsKeepAlive = false;
   deleted = false;

}

/////////////////////////////////////////////////////////////////
VirtualTableImpl::VirtualTableImpl
     ( IndexInvokableGetter* getter
     , ObjectNameGetter * objNameGetter
     , unsigned int numberOfVPTR
     , const std::type_info& refTypeInfo)

     : numberOfVptr(numberOfVPTR)
     , indexInvokableGetter(getter)
     , nameGetter(objNameGetter)
     , expectsBeingDeleted(false)
     , expectsKeepAlive(false)
{
   if(numberOfVptr == 0)
   {
      numberOfVptr = 1;
   }

   validateNumberOfVptr();

   fakeObject = new FakeObject();
   void** vptr = fakeObject->vptr;

   vtbl = createVtbls(numberOfVptr);

   initializeVtbls(vptr, vtbl, numberOfVptr,refTypeInfo, true);

   vptr[MOCKCPP_MAX_INHERITANCE] = (void*)this;

   deleted = false;

   reset();
}

/////////////////////////////////////////////////////////////////
VirtualTableImpl::~VirtualTableImpl()
{
    if(fakeObject != 0)
    {
       delete fakeObject;
    }

    if(vtbl != 0)
    {
       freeVtbls(vtbl, numberOfVptr);
       vtbl = 0;
    }
}

/////////////////////////////////////////////////////////////////
VirtualTable::VirtualTable
    ( IndexInvokableGetter* invokableGetter
    , ObjectNameGetter* nameGetter
    , unsigned int numberOfVptr
    , const std::type_info& info)
    : This( new VirtualTableImpl
               ( invokableGetter
               , nameGetter
               , numberOfVptr
               , info))
{}

/////////////////////////////////////////////////////////////////
VirtualTable::~VirtualTable()
{ delete This; }

/////////////////////////////////////////////////////////////////
void*
VirtualTable::toPointerToInterface() const
{
    return (void*)This->fakeObject;
}
 
/////////////////////////////////////////////////////////////////
void
VirtualTable::addMethod(void* methodAddr, unsigned int indexOfVtbl, unsigned int indexOfVptr)
{
    This->validateIndexOfVtbl(indexOfVtbl);
    This->validateIndexOfVptr(indexOfVptr);

    This->vtbl[getRealVtblIndex(indexOfVptr, indexOfVtbl)] = methodAddr;
}

/////////////////////////////////////////////////////////////////
namespace
{
   struct DummyClass {};

   template <unsigned int VPTRIndex, typename T = DummyClass >
   struct DestructorHolder
   {
      void destructor(void*)
      {
         VirtualTableImpl* pThis = getVirtualTableImpl(this, VPTRIndex);
         if(pThis->expectsKeepAlive)
         {
            MOCKCPP_REPORT_FAILURE("trying to delete an object expected keeping alive.");
         }

         // FIXME: The memory won't be freed automatically.
         // Weird!!!!
         // delete [] pThis->vtbl;
         if(pThis->deleted)
         {
            MOCKCPP_REPORT_FAILURE("object has been deleted previously, you are deleting it again.");
         }

         pThis->deleted = true;
      }
   };
}

#define MOCKCPP_GET_DESTRUCTOR_ADDR(I) \
   case I: \
      destructorAddr = getAddrOfMethod(&DestructorHolder<I, DummyClass>::destructor); \
      break;

/////////////////////////////////////////////////////////////////
void
VirtualTable::setDestructor(unsigned int vptrIndex, unsigned int vtblIndex)
{
    void * destructorAddr = 0;

    This->validateIndexOfVptr(vptrIndex);
    This->validateIndexOfVtbl(vtblIndex);

    switch(vptrIndex)
    {
    #include <mockcpp/DestructorAddrGetterDef.h>
    }

    This->vtbl[getRealVtblIndex(vptrIndex, vtblIndex)] = destructorAddr;
}

/////////////////////////////////////////////////////////////////
void
VirtualTable::reset()
{
    This->reset();
}

/////////////////////////////////////////////////////////////////
void
VirtualTable::verify()
{
   if(This->expectsBeingDeleted && !This->deleted)
   {
      MOCKCPP_REPORT_FAILURE("Object is expected Being Deleted, but it actually didn't happen.");
   }

   This->expectsBeingDeleted = false;
   This->expectsKeepAlive = false;
}

/////////////////////////////////////////////////////////////////
void
VirtualTable::expectsBeingDeleted()
{
    if(This->expectsKeepAlive)
    {
       MOCKCPP_REPORT_FAILURE("What do you really want? You are expecting "
                    "to delete an object alive which you expected "
                    "it should keep alive");
    }

    This->expectsBeingDeleted = true;
}

/////////////////////////////////////////////////////////////////
void
VirtualTable::expectsKeepAlive()
{
   if(This->deleted)
   {
       MOCKCPP_REPORT_FAILURE("The object you expects keeping alive has actually been deleted.");
   }

   if(This->expectsBeingDeleted)
   {
       MOCKCPP_REPORT_FAILURE("What do you really want? You are expecting "
                    "to keep an object alive which you expected "
                    "it should be deleted");
   }
   This->expectsKeepAlive = true;
}

/////////////////////////////////////////////////////////////////
IndexInvokableGetter*
VirtualTable::getInvokableGetter(void* caller, unsigned int vptrIndex)
{
   VirtualTableImpl* pThis = getVirtualTableImpl(caller, vptrIndex);
   if(pThis->deleted)
   {
       MOCKCPP_REPORT_FAILURE("The object you are trying to access has been deleted.");
   }

   return pThis->indexInvokableGetter;
}

#ifdef _MSC_VER

  #include<windows.h>
  #include<dbghelp.h>
  #pragma comment(lib, "Dbghelp.lib")

  namespace {
    std::string PmfInfo2ClsName(const char* pmf_info) {
      const char* from = NULL;
      while(*pmf_info) {
        if(*pmf_info == '(')
          from = strchr(pmf_info, ' ') + 1;
        else if(*pmf_info == ')') {
          return std::string(from, pmf_info - from - 3);
        }
        ++pmf_info;
      }
      return NULL; // impossible return
    }
  }

#else

  #include <sys/mman.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <link.h>
  #include <string.h>
  #include <unistd.h>
  #include <cassert>
  #include <cxxabi.h>

  namespace {
    template<typename Elf_Ehdr, typename Elf_Shdr, typename Elf_Sym>
    void* findVtblAddr(const char* base, const char* pmfName)
    {
      const Elf_Ehdr* elf_header = (const Elf_Ehdr*)base;
      const Elf_Shdr* elf_section = (const Elf_Shdr*)(base + elf_header->e_shoff);
      const char* symTable = base + elf_section[elf_header->e_shnum - 1].sh_offset;
      for(int i = 1; i < elf_header->e_shnum; ++i) {
        if(strstr(base + elf_section[elf_header->e_shstrndx].sh_offset + elf_section[i].sh_name, "sym")) {
          int symEntries = elf_section[i].sh_size / sizeof(Elf_Sym);
          const Elf_Sym* symAddr = (const Elf_Sym*)(base + elf_section[i].sh_offset);
          for(int j = 0; j < symEntries; ++j) {
            if(ELF32_ST_TYPE(symAddr[j].st_info) != 1 || strncmp(symTable + symAddr[j].st_name, "_ZTV", 4) || !symAddr[j].st_value)
              continue;
            const char* symClsName = symTable + symAddr[j].st_name + 4;
            const char* outterLib = strchr(symClsName, '@');
            if(!strncmp(symClsName, pmfName + 1, outterLib ? outterLib - symClsName : strlen(symClsName))) {
              return (void*)(long)(symAddr[j].st_value + 16);
            }
          }
        }
      }
      return NULL;
    }
  }

#endif

void*
VirtualTable::getVtblAddrByVmfPtr(void* pmf, const std::type_info& mf_info, const std::string& name)
{
#ifdef _MSC_VER

  HANDLE hProcess = GetCurrentProcess();
  SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
  if(!SymInitialize(hProcess, NULL, TRUE)) {
    MOCKCPP_REPORT_FAILURE("Failed to call SymInitialize.");
    return NULL;
  }

  uint64_t buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME + sizeof(uint64_t) - 1) / sizeof(uint64_t)];
  PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
  pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
  pSymbol->MaxNameLen = MAX_SYM_NAME;

  char szSymbolName[MAX_SYM_NAME];
  sprintf_s(szSymbolName, MAX_SYM_NAME, "%s::%s", PmfInfo2ClsName(mf_info.name()).c_str(), name.c_str() + name.find_last_of(':') + 1);
  // sprintf_s(szSymbolName, MAX_SYM_NAME, "%s::`vftable'", PmfInfo2ClsName(mf_info.name()).c_str());
  if(!SymFromName(hProcess, szSymbolName, pSymbol)) {
    SymCleanup(hProcess);
    MOCKCPP_ASSERT_TRUE("Failed to get vftable", GetLastError() == 126);
    return NULL;
  }

  SymCleanup(hProcess);
  return (void*)pSymbol->Address;

#else

  struct stat sb;
  Dl_info dlinfo;
  int fd = -1;
  void* ret = NULL;
  if(dladdr(pmf, &dlinfo))
    fd = open(dlinfo.dli_fname, O_RDONLY);
  if(fd < 0)
    goto CLOSE_FD;
  if(fstat(fd, &sb))
    goto CLOSE_FD;
  {
    char* base = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(base == MAP_FAILED)
      goto CLOSE_FD;
    switch(base[EI_CLASS]) {
      case 1:
        ret = findVtblAddr<Elf32_Ehdr, Elf32_Shdr, Elf32_Sym>(base, mf_info.name());
        break;
      case 2:
        ret = findVtblAddr<Elf64_Ehdr, Elf64_Shdr, Elf64_Sym>(base, mf_info.name());
        break;
    }
    munmap(base, sb.st_size);
  }
CLOSE_FD:
  if(fd != -1) close(fd);
  return ret;

#endif
}

MOCKCPP_NS_END
