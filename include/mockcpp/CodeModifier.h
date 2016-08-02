***/

#ifndef __MOCKCPP_CODEMODIFIER_H__
#define __MOCKCPP_CODEMODIFIER_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct CodeModifier
{
	static bool modify(void *dest, const void *src, size_t size);
};

MOCKCPP_NS_END

#endif

