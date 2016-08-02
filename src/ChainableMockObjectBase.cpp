
#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockObjectBase.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/ChainableMockMethodContainer.h>
#include <mockcpp/ReportFailure.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
struct ChainableMockObjectBaseImpl
{
    ChainableMockObjectBaseImpl(const std::string& name);

    ChainableMockMethodContainer container;
    const std::string objectName;
};

//////////////////////////////////////////////////////////////
ChainableMockObjectBaseImpl::
ChainableMockObjectBaseImpl(const std::string& name)
   : objectName(name)
{
}

//////////////////////////////////////////////////////////////
ChainableMockObjectBase::
ChainableMockObjectBase(const std::string& name)
	: shared(false), This(new ChainableMockObjectBaseImpl(name))
{
}

//////////////////////////////////////////////////////////////
ChainableMockObjectBase::
ChainableMockObjectBase(const ChainableMockObjectBase& obj)
   : shared(true), This(obj.This)
{
}

//////////////////////////////////////////////////////////////
ChainableMockObjectBase::~ChainableMockObjectBase()
{
    if(!shared)
    {
	    delete This;
    }
}

//////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockObjectBase::
getInvocationMocker(const std::string& id) const
{
    return This->container.findInvocationMocker(id);
}

//////////////////////////////////////////////////////////////
void
ChainableMockObjectBase::verify()
{
    try {
       This->container.verify();
    }
    catch(std::exception& ex)
    {
       MOCKCPP_REPORT_FAILURE(ex.what());
    }
}

//////////////////////////////////////////////////////////////
const std::string&
ChainableMockObjectBase::getName() const
{
    return This->objectName;
}

//////////////////////////////////////////////////////////////
ChainableMockMethodContainer*
ChainableMockObjectBase::getMethodContainer() const
{
   return &This->container;
}

//////////////////////////////////////////////////////////////

MOCKCPP_NS_END


