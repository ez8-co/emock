/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

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

#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

RefAny::RefAny() {}

#if 0
RefAny::RefAny(const char* value)
      : AnyBase(new RefHolder<const char*>(value))
{
}

RefAny::RefAny(char* value)
      : AnyBase(new RefHolder<char*>(value))
{
}

#endif

RefAny::RefAny(const RefAny & other)
      : AnyBase(other.getContent() ? other.getContent()->clone() : 0)
{
}

RefAny& RefAny::operator=(const RefAny & rhs)
{
   RefAny(rhs).swap(*this);
   return *this;
}

RefAny& getEmptyRefAny()
{
    return const_cast<RefAny&>(EmptyRefAny);
}
/////////////////////////////////////////////////////

MOCKCPP_NS_END

