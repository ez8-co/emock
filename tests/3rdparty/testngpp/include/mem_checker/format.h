/***
    testngpp is a generic C/C++ test framework.
    Copyright (C) <2010>  <Chen Guodong: sinojelly@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef __FORMAT_H__
#define __FORMAT_H__

#include <sstream>
#include <iomanip>

// safe strncpy, padding a nul at the end of to string, even from is longger than count.
#define strncpy_n(to, from, count) strncpy(to, from, count - 1)[count - 1] = '\0'

#define POINTER(pointer) \
			" 0x"  \
            << std::hex << std::setiosflags(std::ios::uppercase)  \
            << std::setw(8) << std::setfill('0') \
            << (unsigned long)(pointer)  \
            << std::dec << std::resetiosflags(std::ios::uppercase) 

#define FILE_LINE(file, line) \
			" (" << file << ", " << line << ")"

#define MEM_SIZE(size) \
			" (" << size << " bytes)"


struct MemAddr
{
	explicit MemAddr(void* _pointer)
		: pointer(_pointer)
	{
	}

	friend std::ostream & operator<<(std::ostream &oss, const MemAddr &pointer);
private:
	void* pointer;
};


struct MemSize
{
	explicit MemSize(unsigned int _size)
		: size(_size)
	{
	}

	friend std::ostream & operator<<(std::ostream &oss, const MemSize &size);
private:	
	unsigned int size;
};

extern bool print_position_from_addr(const void* addr, unsigned int &line, char *file_buf, unsigned int file_buf_size);

struct SrcAddr
{
	SrcAddr(const char *_file, unsigned int _line, void *_instruction)
		: file(_file), line(_line)
	{
	    if (line == 0) 
	    {
	        file = last_info;
	        if (!print_position_from_addr(_instruction, line, last_info, sizeof(last_info))) // fail to get source location
	        {
	        	sprintf(last_info, "instruction 0x%016lX", (unsigned long)_instruction);
	        }
	    }
	}

	friend std::ostream & operator<<(std::ostream &oss, const SrcAddr &addr);
private:
	const char *file;
	unsigned int line;
	char last_info[256];
};

struct MemContent
{
	explicit MemContent(const void* _pointer, unsigned int _maxSize)
		: pointer(_pointer), maxSize(_maxSize)
	{
	}

	friend std::ostream & operator<<(std::ostream &oss, const MemContent &pointer);
private:
	const void* pointer;
	unsigned int maxSize;
};

std::ostream & operator<<(std::ostream &oss, const MemAddr &pointer)
{
	oss << POINTER(pointer.pointer);
	return oss;
}

std::ostream & operator<<(std::ostream &oss, const MemSize &size)
{
	oss << MEM_SIZE(size.size);
	return oss;
}	

std::ostream & operator<<(std::ostream &oss, const SrcAddr &addr)
{
	oss << FILE_LINE(addr.file, addr.line);
	return oss;
}

std::ostream & operator<<(std::ostream &oss, const MemContent &addr)
{
	oss << std::hex << std::setiosflags(std::ios::uppercase);
	
	unsigned int size = addr.maxSize < 10 ? addr.maxSize : 10; // output 10 bytes at most
	for (unsigned int i = 0; i < size; i++)
	{
        unsigned int temp = (((unsigned int)(*((const char *)addr.pointer + i))) & 0xff);
		oss << std::setw(2) << std::setfill('0') 
		    << temp << " ";
	}

	oss << std::dec << std::resetiosflags(std::ios::uppercase); 

	return oss;
}

#endif

