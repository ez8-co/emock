/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
