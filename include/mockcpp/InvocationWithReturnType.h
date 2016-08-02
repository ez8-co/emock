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

#ifndef __MOCKCPP_INVOCATION_WITH_RETURN_TYPE_H
#define __MOCKCPP_INVOCATION_WITH_RETURN_TYPE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

template <typename RT>
struct InvocationWithReturnType : public Invocation
{
	InvocationWithReturnType(
               const RefAny& p1 = RefAny()
             , const RefAny& p2 = RefAny()
             , const RefAny& p3 = RefAny()
             , const RefAny& p4 = RefAny()
             , const RefAny& p5 = RefAny()
             , const RefAny& p6 = RefAny())
		: Invocation(p1, p2, p3, p4, p5, p6)
	{}

   std::string toString(void) const;

	bool matches(Stub* stub) const
	{
      return stub->type() == typeid(RT);
	}
};

MOCKCPP_NS_END

#endif

