
#ifndef __MOCKCPP_JMP_CODE_X32_H__
#define __MOCKCPP_JMP_CODE_X32_H__

const unsigned char jmpCodeTemplate[]  = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
#define SET_JMP_CODE(base, from, to) do { \
        *(unsigned long*)(base + 1) = \
            (unsigned long)to - (unsigned long)from - sizeof(jmpCodeTemplate); \
   } while(0)

#endif

