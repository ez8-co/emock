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

#ifndef __MOCKCPP_REPEAT_STUB_H
#define __MOCKCPP_REPEAT_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

struct RepeatStub : public TypelessStub
{
    RepeatStub(const Any& value, unsigned int times);

    bool isCompleted() const;

    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:

    Any returnValue;
    unsigned int repeatedTimes;
    const unsigned int repeatTimes;
};

MOCKCPP_NS_END

#endif

