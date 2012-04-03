
#ifndef __MOCKCPP_JMP_CODE_ARCH_H__
#define __MOCKCPP_JMP_CODE_ARCH_H__

#include <mockcpp/mockcpp.h>

#if BUILD_FOR_X64
# include "JmpCodeX64.h"
#elif BUILD_FOR_X86
# include "JmpCodeX86.h"
#endif

#endif

