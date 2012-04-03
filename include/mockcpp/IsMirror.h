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

#ifndef __MOCKCPP_IS_MIRROR_H
#define __MOCKCPP_IS_MIRROR_H

#include <mockcpp/Constraint.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
template <typename T>
struct IsMirrorBase
{
};

///////////////////////////////////////////////////////
template <typename T>
struct IsMirrorBase<T*>: public Constraint
{
public:

    IsMirrorBase(T* p, size_t size)
      : pointer(0), sizeOfBuffer(size)
    {
      if (size != 0)
      {
        pointer = (T*)(new char [sizeOfBuffer+1]);
        ::memset((void*)pointer, 0, sizeOfBuffer+1);
        ::memcpy((void*)pointer, (void*)p, sizeOfBuffer);
      }
    }

    ~IsMirrorBase()
    {
      if (pointer != 0)
      {
        delete [] (char*)pointer;
      }
    }

    bool eval(const RefAny& val) const
    {
      if (!any_castable<T*>(val))
      {
        return false;
      }

      T* p = any_cast<T*>(val);
      if (p == 0)
      {
        return false;
      }

      return !memcmp((void*)p, (void*)pointer, sizeOfBuffer);
    }

    std::string toString() const
    {
      oss_t oss;

      oss << "mirror("
          << MOCKCPP_NS::toTypeAndValueString(pointer)
          << ", " << sizeOfBuffer
          << ")";

      return oss.str();
    }

private:

    T* pointer;

    size_t sizeOfBuffer;
};

//////////////////////////////////////////////////////////////////////
template <typename T>
struct IsMirror : public Constraint
{

#if defined(__GNUC__) && (__GNUC__ > 3)
public:

   IsMirror(const T& obj)
     : object(obj)
   {
   }

   bool eval(const RefAny& val) const
   {
      if (!any_castable<T>(val))
      {
        return false;
      }

      T p = any_cast<T>(val);
      return !memcmp((void*)&p, (void*)&object, sizeof(object));
   }
   
   std::string toString(void) const
   {
      oss_t oss;

      oss << "mirror("
          << MOCKCPP_NS::toTypeAndValueString(object)
          << ")";

      return oss.str();
   }

private:

   T object;
#endif

};

//////////////////////////////////////////////////////////////////////
template <typename T>
struct IsMirror<T*> : public IsMirrorBase<T*>
{
public:

   IsMirror(T* p, size_t size = 0)
      : IsMirrorBase<T*>(p, size == 0 ? sizeof(T) : size)
   {
   }
};

//////////////////////////////////////////////////////////////////////
template <>
struct IsMirror<void*> : public IsMirrorBase<void*>
{
public:

    IsMirror(void* p, size_t size)
      : IsMirrorBase<void*>(p, size)
    {
      MOCKCPP_ASSERT_TRUE_MESSAGE(
            "parameter \"size\" of IsMirror<void*> cannot be specified as 0", 
            size > 0);
    }

};

MOCKCPP_NS_END

#endif

