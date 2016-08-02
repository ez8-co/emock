
#ifndef __MOCKCPP_JMP_CODE_H__
#define __MOCKCPP_JMP_CODE_H__

#include <stddef.h>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct JmpCodeImpl;

struct JmpCode
{
    JmpCode(const void* from, const void* to);
    ~JmpCode();
    
    void*  getCodeData() const;
    size_t getCodeSize() const;
private:
	JmpCodeImpl* This;
};

MOCKCPP_NS_END

#endif

