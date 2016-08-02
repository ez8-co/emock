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

#include <mockcpp/ProcStub.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////
struct ProcStubBaseImpl
{
    ProcStubBaseImpl(const std::string& name, void* addr)
       : procName(name), address(addr)
    {}
    
    std::string describeSelf() const ;

    std::string procName;
    void* address;
};

///////////////////////////////////////////////////////////////
ProcStubBase::ProcStubBase(const std::string& name, void* addr)
   : This(new ProcStubBaseImpl(name, addr))
{}

///////////////////////////////////////////////////////////////
ProcStubBase::~ProcStubBase()
{
    delete This;
}

///////////////////////////////////////////////////////////////
bool ProcStubBase::isCompleted() const
{
    return true;
}

///////////////////////////////////////////////////////////////
std::string ProcStubBase::toString() const
{
    oss_t oss;

    oss << "invoke(" << This->describeSelf() << ")";

    return oss.str();
}

///////////////////////////////////////////////////////////////
std::string ProcStubBaseImpl::describeSelf() const
{
    if(procName.size() > 0)
       return procName;

    oss_t oss;

    oss << address;

    return oss.str();
}

///////////////////////////////////////////////////////////////
std::string getParameterMismatchString(int n, 
               std::string p, const Invocation& inv)
{
    oss_t oss;
    oss << "Parameter " << n << " mismatch, required: [" << p  << "]"
        << " actual: [" << inv.getParameter(n).toTypeString() << "]"; 

    return oss.str();
}

///////////////////////////////////////////////////////////////

MOCKCPP_NS_END
