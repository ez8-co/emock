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

#include <emock/emock.h>

#include <emock/ChainableMockObjectBase.h>
#include <emock/ChainableMockMethodCore.h>
#include <emock/InvocationMocker.h>
#include <emock/ChainableMockMethodContainer.h>
#include <emock/ReportFailure.h>

EMOCK_NS_START

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
       EMOCK_REPORT_FAILURE(ex.what());
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

EMOCK_NS_END


