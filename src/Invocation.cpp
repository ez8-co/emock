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


#include <vector>

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
namespace
{
    const static unsigned int maxNumOfParameters = 12;
};

////////////////////////////////////////////////////////////////
struct InvocationImpl
{
    std::vector<RefAny> parameters;
    std::string nameOfCaller;

    std::string toString(void) const;

    InvocationImpl(const std::string& name);
};

////////////////////////////////////////////////////////////////
InvocationImpl::InvocationImpl(const std::string &name)
: nameOfCaller(name)
{
}
////////////////////////////////////////////////////////////////
std::string InvocationImpl::toString() const
{
    oss_t oss;

    for (unsigned int i=0; i<maxNumOfParameters; i++)
    {
      if (parameters[i].empty())
          return oss.str();

      if (i > 0) oss << ", ";

      oss << parameters[i].toTypeAndValueString();
    }

    return oss.str();
}

////////////////////////////////////////////////////////////////

#define INIT_PARAMETER(i) This->parameters.push_back(p##i)

Invocation::Invocation(
                     const std::string name
                   , const RefAny& p1
                   , const RefAny& p2
                   , const RefAny& p3
                   , const RefAny& p4
                   , const RefAny& p5
                   , const RefAny& p6
                   , const RefAny& p7
                   , const RefAny& p8
                   , const RefAny& p9
                   , const RefAny& p10
                   , const RefAny& p11
                   , const RefAny& p12
   )
   : This(new InvocationImpl(name))
{
    INIT_PARAMETER(1);
    INIT_PARAMETER(2);
    INIT_PARAMETER(3);
    INIT_PARAMETER(4);
    INIT_PARAMETER(5);
    INIT_PARAMETER(6);
    INIT_PARAMETER(7);
    INIT_PARAMETER(8);
    INIT_PARAMETER(9);
    INIT_PARAMETER(10);
    INIT_PARAMETER(11);
    INIT_PARAMETER(12);
}

////////////////////////////////////////////////////////////////
Invocation::~Invocation()
{
    delete This;
}

////////////////////////////////////////////////////////////////
RefAny& Invocation::getParameter(const unsigned int i) const
{
    if (i < 1 || i > maxNumOfParameters )
    {
       return getEmptyRefAny();
    }

    return This->parameters[i-1];
}

////////////////////////////////////////////////////////////////
std::string Invocation::toString(void) const
{
    return std::string("(") + This->toString() + std::string(")");
}

////////////////////////////////////////////////////////////////

std::string Invocation::getNameOfCaller() const
{
    return This->nameOfCaller;
}

////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

