
#ifndef __MOCKCPP_JMP_CODE_X64_H__
#define __MOCKCPP_JMP_CODE_X64_H__

// FF 25 : JMP /4   jmp absolute indirect
// bytes 2 ~ 5 : operand of jmp, relative to the memory that recorded the thunk addr. it should be zero.
// bytes 6 ~ 13 : the absolute addr of thunk.
const unsigned char jmpCodeTemplate[]  =
   { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define SET_JMP_CODE(base, from, to) do { \
       *(uintptr_t *)(base + 6) = (uintptr_t)to; \
   } while(0)

#endif

