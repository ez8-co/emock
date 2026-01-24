/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.

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

#ifndef __EMOCK_API_HOOK_TARGET_RESOLVER_H__
#define __EMOCK_API_HOOK_TARGET_RESOLVER_H__

#include <stddef.h>

#include <emock/emock.h>

EMOCK_NS_START

class ApiHookTargetResolver
{
public:
    ApiHookTargetResolver(const void* from, unsigned int max_depth)
        : m_target(getChainTarget(from, max_depth)) {}

    const void* getTarget() const
    {
        return m_target;
    }

private:
    enum class JmpInstruction
    {
        Relative,      // E9/EB xx xx xx
        Absolute,      // FF 25 xx xx xx xx
        Other,
    };

    static const void* getChainTarget(const void* from, unsigned int max_depth);

    static JmpInstruction analyzeInstruction(const unsigned char* code);

    static const unsigned char* resolveRelativeJump(const unsigned char* code);

    static const unsigned char* resolveAbsoluteJump(const unsigned char* code);

    const void* m_target;
};

EMOCK_NS_END

#endif

