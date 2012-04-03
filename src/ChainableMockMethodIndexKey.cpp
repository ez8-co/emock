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

#include <mockcpp/ChainableMockMethodIndexKey.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ChainableMockMethodIndexKey::ChainableMockMethodIndexKey(
      unsigned int vptrIndex, unsigned int vtblIndex)
    : index(vptrIndex*MOCKCPP_MAX_VTBL_SIZE + vtblIndex)
{
}

////////////////////////////////////////////////////////////
bool ChainableMockMethodIndexKey::equals(
      const ChainableMockMethodKey* const rhs) const
{
    if(rhs == 0)
    {
       return false;
    }

    if(this == rhs)
    {
       return true;
    }

    ChainableMockMethodIndexKey* key = \
          dynamic_cast<ChainableMockMethodIndexKey*> \
             (const_cast<ChainableMockMethodKey*>(rhs));
    if(key == 0)
    {
       return 0;
    }
     
    return key->getIndex() == this->getIndex();
}

///////////////////////////////////////////////////////////
unsigned int ChainableMockMethodIndexKey::getIndex() const
{
   return index;
}

MOCKCPP_NS_END
