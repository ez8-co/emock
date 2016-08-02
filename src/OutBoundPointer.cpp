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

#include <mockcpp/OutBoundPointer.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////////////////
void OutBoundPointerCheckConst(const std::string& typeString, bool isConst) 
{
   oss_t oss;

   oss << "A constant pointer " << typeString
       << " cannot be outbounded";

   MOCKCPP_ASSERT_FALSE_MESSAGE( oss.str(), isConst);
}

////////////////////////////////////////////////////////////////////////////
OutBoundPointer<void*>::OutBoundPointer(void* p, size_t size, Constraint* constraint)
	 : OutBoundPointerBase<void*>(p, size, constraint)
{
	MOCKCPP_ASSERT_TRUE_MESSAGE(
            "parameter \"size\" of OutBoundPointer<void*> cannot be specified as 0",
            size > 0);
}

////////////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

