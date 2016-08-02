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

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/DecoratedConstraint.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////////
DecoratedConstraint::DecoratedConstraint(Constraint* constraint)
      : decoratedConstraint(constraint)
{}

/////////////////////////////////////////////////////////////////////
DecoratedConstraint::~DecoratedConstraint()
{
    delete decoratedConstraint;
}

/////////////////////////////////////////////////////////////////////
bool DecoratedConstraint::eval(const RefAny& val) const
{
    if (hasDecoratedConstraint() && !decoratedConstraint->eval(val))
    {
      return false;
    }

    return evalSelf(val);
}

/////////////////////////////////////////////////////////////////////
std::string DecoratedConstraint::getDecoratedConstraintString() const
{
    return hasDecoratedConstraint() ? 
           std::string(", ") + decoratedConstraint->toString() : "";
}
    
/////////////////////////////////////////////////////////////////////
bool DecoratedConstraint::hasDecoratedConstraint() const
{
    return decoratedConstraint != 0;
}

/////////////////////////////////////////////////////////////////////
std::string DecoratedConstraint::toString() const
{
    oss_t oss;

    oss << getName() << "(" << getTypeAndValueString()
        << getDecoratedConstraintString() << ")";

    return oss.str();
}


MOCKCPP_NS_END


