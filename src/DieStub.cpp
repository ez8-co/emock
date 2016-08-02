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

#include <stdlib.h>

#include <mockcpp/DieStub.h>


MOCKCPP_NS_START

/////////////////////////////////////////////////
DieStub::DieStub(int exitCode)
   : code(exitCode)
{
}

/////////////////////////////////////////////////
bool DieStub::isCompleted() const
{
	return false;
}

/////////////////////////////////////////////////
Any& DieStub::invoke(void)
{
   ::exit(code);

   return getEmptyAny();
}

/////////////////////////////////////////////////
std::string DieStub::toString() const
{
   oss_t oss;

   oss << "die(" << code << ")";

   return oss.str();
}

/////////////////////////////////////////////////
const std::type_info& DieStub::type() const
{
   return typeid(void);
}

MOCKCPP_NS_END

