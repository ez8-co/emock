/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/


// for new/delete
#include <new>
#include <stdlib.h>
#include <stdio.h>

#include <inttypes.h>

// for error string
#include <sstream>

#if !defined(_MSC_VER)
// for opened fd checking
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

#include <testngpp/runner/ResourceCheckPoint.h>
#include <testngpp/internal/AssertionFailure.h>
#include <testngpp/internal/Error.h>

#if defined(_MSC_VER)
#define snprintf _snprintf
#endif

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////////
namespace
{
   size_t allocatedSize = 0;
}

unsigned int getNumberOfOpenFiles()
{
#if defined(_MSC_VER)
    return 0;
#else
    unsigned int maxNumberOfOpenFiles = ::getdtablesize();
    unsigned int openedFiles = 0;
    for(unsigned int fd = 0; fd < maxNumberOfOpenFiles; fd++)
    {
       int flags = 0;
       do{
         flags = ::fcntl(fd, F_GETFD, 0);
       } while(flags == -1 && errno == EINTR);

       if(flags != -1)
       {
         openedFiles++;
       }
    }

    return openedFiles;
#endif
}

//////////////////////////////////////////////////////////////////
ResourceCheckPoint testngppSetCheckPoint()
{
   ResourceCheckPoint cp;

   cp.memory = allocatedSize;
   cp.fds = getNumberOfOpenFiles();

   return cp;
}

//////////////////////////////////////////////////////////////////
void testngppVerifyCheckPoint(const ResourceCheckPoint& rcp
      , const char* file, unsigned int line) 
{
   if(rcp.memory != allocatedSize)
   {
      std::stringstream ss;
      ss << "memory leaked (" << (int)(allocatedSize - rcp.memory) << ") bytes.";
      throw AssertionFailure(file, line, ss.str());
   }

   unsigned int nfds = getNumberOfOpenFiles();
   if(rcp.fds != nfds)
   {
      std::stringstream ss;
      ss << "resource leaking, there are (" 
         << (int)(nfds - rcp.fds) 
         << ") opened file descriptors were not closed.";
      throw AssertionFailure(file, line, ss.str());
   }
}

//////////////////////////////////////////////////////////////////
namespace
{
   static const unsigned int magicNumber = 0xFAB587CD;

   struct BlockHeader
   {
      size_t size;
      unsigned int magic;
   };

   struct EndBlock
   {
      unsigned int magic;
   };
}

//////////////////////////////////////////////////////////////////
static void* allocateMemory(size_t size) TESTNGPP_THROW(std::bad_alloc)
{

   BlockHeader* header = (BlockHeader*)::malloc(
               size + sizeof(BlockHeader) + sizeof(EndBlock));
   if(header == 0)
   {
      throw std::bad_alloc();
   }

   header->size = size;
   header->magic = magicNumber;

   allocatedSize += size;

   void * p = (void*)((char*)header + sizeof(BlockHeader));

   EndBlock* endBlock = (EndBlock*)((char*)p + size);
   endBlock->magic = magicNumber;

   return p;
}

//////////////////////////////////////////////////////////////////
static void freeMemory(void* p) 
{
   if(p == 0)
   {
      return;
   }

   BlockHeader* header = (BlockHeader*)((char*)p - sizeof(BlockHeader));

   if(header->magic != magicNumber)
   {
      char buf[100];
      snprintf(buf, sizeof(buf), "memory corruption occurred at %#"PRIxPTR, (uintptr_t) p);
      throw Error(buf);
   }

   allocatedSize -= header->size;

   EndBlock* endBlock = (EndBlock*)((char*)p + header->size);

   if(endBlock->magic != magicNumber)
   {
      throw Error("Memory Corruption");
   }

   endBlock->magic = 0;

   ::free(header);
}

TESTNGPP_NS_END

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
USING_TESTNGPP_NS

#if 0 
//////////////////////////////////////////////////////////////////
void* operator new (size_t size) TESTNGPP_THROW(std::bad_alloc)
{
    return allocateMemory(size);
}

//////////////////////////////////////////////////////////////////
void* operator new [] (size_t size) TESTNGPP_THROW(std::bad_alloc)
{
    return allocateMemory(size);
}

//////////////////////////////////////////////////////////////////
void operator delete (void * p)
{
    freeMemory(p);
}

//////////////////////////////////////////////////////////////////
void operator delete [] (void * p)
{
    freeMemory(p);
}
#endif

//////////////////////////////////////////////////////////////////
