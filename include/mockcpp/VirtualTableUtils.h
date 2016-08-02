
#ifndef __MOCKCPP_VIRTUAL_TABLE_UTILS_H
#define __MOCKCPP_VIRTUAL_TABLE_UTILS_H

#include <typeinfo>
#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

void** createVtbls(unsigned int numberOfVptr);
void freeVtbls(void** vtbl, unsigned int numberOfVtpr);
unsigned int getRealVtblIndex(unsigned int indexOfVptr, unsigned int indexOfVtbl);
void initializeVtbls(void** vptr, void**vtbl, unsigned int numberOfVtpr, const std::type_info& info, bool hasRtti);

MOCKCPP_NS_END

#endif
