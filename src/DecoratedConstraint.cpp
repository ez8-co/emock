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


