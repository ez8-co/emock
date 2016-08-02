
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
