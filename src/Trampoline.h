/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
***/

#ifndef __EMOCK_TRAMPOLINE_H
#define __EMOCK_TRAMPOLINE_H

#include <emock/emock.h>

EMOCK_NS_START

class Trampoline
{
public:
   static void* get(const void* src, void* dst);
   static void* get4MemFunc(const void* src, void* dst);

   static void reset();
};

EMOCK_NS_END

#endif
