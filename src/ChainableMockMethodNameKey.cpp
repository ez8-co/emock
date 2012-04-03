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

#include <mockcpp/ChainableMockMethodNameKey.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
ChainableMockMethodNameKey::
ChainableMockMethodNameKey(const std::string& name)
   : methodName(name)
{
}

/////////////////////////////////////////////////////
bool
ChainableMockMethodNameKey::
equals(const ChainableMockMethodKey * const rhs) const
{
   if(rhs == 0)
   {
      return false;
   }

   if(rhs == this)
   {
      return true;
   }

   ChainableMockMethodNameKey* key = \
          dynamic_cast<ChainableMockMethodNameKey*>(
              const_cast<ChainableMockMethodKey*>(rhs));
   if(key == 0)
   {
      return false;
   }
   
   return key->getMethodName() == this->getMethodName();
}

/////////////////////////////////////////////////////
std::string&
ChainableMockMethodNameKey::
getMethodName() const
{
   return const_cast<std::string&>(this->methodName);
}

/////////////////////////////////////////////////////

MOCKCPP_NS_END

