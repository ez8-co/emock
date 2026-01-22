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

#include <stdint.h>

#include <emock/ApiHookTargetResolver.h>

USING_EMOCK_NS

ApiHookTargetResolver::JmpInstruction ApiHookTargetResolver::analyzeInstruction(const unsigned char* code)
{
    if (code[0] == 0xE9) 
    {
        // JMP rel32
        return JmpInstruction::Relative;
    }
    else if (code[0] == 0xEB) 
    {
        // JMP rel8
        return JmpInstruction::Relative;
    }
    else if (code[0] == 0xFF && code[1] == 0x25) 
    {
        // JMP [disp32]
        return JmpInstruction::Absolute;
    }
    else
    {
        return JmpInstruction::Other;
    }
}

const void* ApiHookTargetResolver::getChainTarget(const void* from, unsigned int max_depth)
{
    const unsigned char* code = static_cast<const unsigned char*>(from);

    uint32_t depth = 0;

    while (depth < max_depth)
    {
        switch (analyzeInstruction(code))
        {
        case JmpInstruction::Relative:
            code = resolveRelativeJump(code);
            break;
        case JmpInstruction::Absolute:
            code = resolveAbsoluteJump(code);
            break;
        case JmpInstruction::Other:
            __fallthrough;
        default:
            return code;
        }

        depth++;
    }

    // If no non-jump code is found after reaching the maximum depth,
    // we need return to the original address.
    return from;
}

const unsigned char* ApiHookTargetResolver::resolveRelativeJump(const unsigned char* code)
{
    if (code[0] == 0xE9) {
        // 32-bit relative jump
        int32_t offset = *reinterpret_cast<int32_t*>(const_cast<unsigned char*>(code) + 1);
        return code + 5 + offset;
    }
    else if (code[0] == 0xEB) {
        // 8-bit relative jump
        int8_t offset = *reinterpret_cast<int8_t*>(const_cast<unsigned char*>(code) + 1);
        return code + 2 + offset;
    }
    return code;
}

const unsigned char* ApiHookTargetResolver::resolveAbsoluteJump(const unsigned char* code)
{
    // FF 25 [disp32] - JMP [target]
    uint32_t disp = *reinterpret_cast<uint32_t*>(const_cast<unsigned char*>(code) + 2);

    // Calculate the target address
    // Note: This refers to RIP relative addressing (x64) or absolute addressing (x86).
#ifdef BUILD_FOR_X64
    // x64: RIP relative addressing
    uintptr_t rip = reinterpret_cast<uintptr_t>(code) + 6;
    unsigned char** targetPtr = reinterpret_cast<unsigned char**>(rip + disp);
#elif BUILD_FOR_X86
    // x86: Absolute address
    unsigned char** targetPtr = reinterpret_cast<unsigned char**>(disp);
#endif

    return *targetPtr;
}
