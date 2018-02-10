/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
***/

#ifndef __EMOCK_SYMBOL_RETRIEVER_H
#define __EMOCK_SYMBOL_RETRIEVER_H

#include <typeinfo>
#include <string>

#include <emock/emock.h>

EMOCK_NS_START

class SymbolRetriever
{
public:
   static void* getAddress(std::string& name, const std::string& matcher);
   static void* getMethodAddress(void* p, const std::type_info& info, const std::string& stringify);
   static void reset();
};

EMOCK_NS_END

#endif
