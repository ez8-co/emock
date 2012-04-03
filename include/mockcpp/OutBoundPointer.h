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

#ifndef __MOCKCPP_OUTBOUND_POINTER_H
#define __MOCKCPP_OUTBOUND_POINTER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/types/AnyCast.h>
#include <mockcpp/DecoratedConstraint.h>
#include <mockcpp/IsConst.h>

MOCKCPP_NS_START

void OutBoundPointerCheckConst(const std::string& typeString, bool isConst);

///////////////////////////////////////////////////////
template <typename T>
struct OutBoundPointerBase
{
};

///////////////////////////////////////////////////////
template <typename T>
struct OutBoundPointerBase<T*>: public DecoratedConstraint
{
public:
    OutBoundPointerBase(T* p, size_t size, Constraint* constraint)
      : DecoratedConstraint(constraint), sizeOfBuffer(size)
    {
      if (size != 0)
      {
        pointer = (T*)(new char [size+1]);
        ::memset((void*)pointer, 0, size+1);
        ::memcpy((void*)pointer, (void*)p, size);
      }
    }

    ~OutBoundPointerBase()
    {
      if (pointer != 0)
      {
        delete [] (char*)pointer;
      }
    }

    bool evalSelf(const RefAny& val) const
    {
      T* p = any_cast<T*>(val);
      if (p == 0)
      {
        return false;
      }

      checkConst();

      (void) memcpy((void*)p, (void*)pointer, sizeOfBuffer);

      return true;
    }

    std::string getName() const
    {
      return "outBoundP";
    }

    std::string getTypeAndValueString() const
    {
      return MOCKCPP_NS::toTypeAndValueString(pointer);
    }

private:

    void checkConst() const
    {
      OutBoundPointerCheckConst(TypeString<T*>::value(), IsConst<T>::isTrue);
    }

private:

    size_t sizeOfBuffer;
    T* pointer;
};

//////////////////////////////////////////////////////////////////////
template <typename T>
struct OutBoundPointer 
{
};

//////////////////////////////////////////////////////////////////////
template <typename T>
struct OutBoundPointer<T*> : public OutBoundPointerBase<T*>
{
public:

   OutBoundPointer(T* p, size_t size = 0, Constraint* constraint = 0)
      : OutBoundPointerBase<T*>(p, size == 0 ? sizeof(T) : size, constraint)
   {
   }
};

//////////////////////////////////////////////////////////////////////
template <>
struct OutBoundPointer<void*>: public OutBoundPointerBase<void*>
{
public:

    OutBoundPointer(void* p, size_t size, Constraint* constraint = 0);
};

MOCKCPP_NS_END

#endif

