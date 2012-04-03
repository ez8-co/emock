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

#ifndef __MOCKCPP_CHECK_WITH_H
#define __MOCKCPP_CHECK_WITH_H

#include <mockcpp/types/AnyCast.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

template <typename T, typename Predict>
struct CheckWith : public Constraint
{
    CheckWith(Predict pred)
      : predict(pred)
    {}    

    bool eval(const RefAny& val) const
    {
      if(!any_castable<T>(val)) return false;
      
      return predict(any_cast<T>(val));
    }

    std::string toString() const
    {
      return std::string("check(") + 
             MOCKCPP_NS::toTypeAndValueString(predict) +
             std::string(")");
    }

private:

    mutable Predict predict;
};

MOCKCPP_NS_END

#endif
