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

#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_INDEX_KEY_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_INDEX_KEY_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockMethodKey.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockMethodIndexKey
    : public ChainableMockMethodKey
{
   ChainableMockMethodIndexKey(unsigned int vptrIndex, unsigned int vtblIndex);

   bool equals(const ChainableMockMethodKey * const rhs) const;

   unsigned int getIndex() const;

private:
   unsigned int index;
};

MOCKCPP_NS_END

#endif

