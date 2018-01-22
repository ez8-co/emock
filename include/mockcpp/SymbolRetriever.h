/***
   mockcpp is a C/C++ mock framework.
   Copyright (c) 2010-2017 <http://ez8.co> <orca.zhang@yahoo.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#ifndef __MOCKCPP_SYMBOL_RETRIEVER_H
#define __MOCKCPP_SYMBOL_RETRIEVER_H

#include <typeinfo>
#include <string>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

class SymbolRetriever
{
public:
   static void* getAddress(void* p, const std::type_info& info, const std::string& stringify);
   static void reset();
};

MOCKCPP_NS_END

#endif
