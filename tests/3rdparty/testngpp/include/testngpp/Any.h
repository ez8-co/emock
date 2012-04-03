
#ifndef TESTNGPP_BOOST_ANY_INCLUDED
#define TESTNGPP_BOOST_ANY_INCLUDED

// what:  variant type boost::any
// who:   contributed by Kevlin Henney,
//        with features contributed and bugs found by
//        Ed Brey, Mark Rodgers, Peter Dimov, and James Curran
// when:  July 2001
// where: tested with BCC 5.5, MSVC 6.0, and g++ 2.95

#include <algorithm>
#include <typeinfo>
#include <string>

#include <testngpp/TypeTraits.h>
#include <testngpp/utils/TypeString.h>

TESTNGPP_NS_START

class any
{
public: // structors

   any()
      : content(0)
   {
   }

   template<typename ValueType>
   any(const ValueType & value)
      : content(new holder<ValueType>(value))
   {
   }

   any(const any & other)
      : content(other.content ? other.content->clone() : 0)
   {
   }

   ~any()
   {
      delete content;
   }

public: // modifiers

   any & swap(any & rhs)
   {
      std::swap(content, rhs.content);
      return *this;
   }

   template<typename ValueType>
   any & operator=(const ValueType & rhs)
   {
      any(rhs).swap(*this);
      return *this;
   }

   any & operator=(any rhs)
   {
      rhs.swap(*this);
      return *this;
   }

public: // queries

   bool empty() const
   {
      return !content;
   }

   const std::type_info & type() const
   {
      return content ? content->type() : typeid(void);
   }

private: // types

   class placeholder
   {
   public: // structors

      virtual ~placeholder()
      {
      }

   public: // queries

      virtual const std::type_info & type() const = 0;

      virtual placeholder * clone() const = 0;

   };

   template<typename ValueType>
   class holder : public placeholder
   {
   public: // structors

      holder(const ValueType & value)
              : held(value)
      {
      }

   public: // queries

      virtual const std::type_info & type() const
      {
         return typeid(ValueType);
      }

      virtual placeholder * clone() const
      {
         return new holder(held);
      }

   public: // representation

      ValueType held;

   private: // intentionally left unimplemented
      holder & operator=(const holder &);
   };


private: // representation

   template<typename ValueType>
   friend ValueType * any_cast(any *);

   template<typename ValueType>
   friend ValueType * unsafe_any_cast(any *);

   placeholder * content;

};

class bad_any_cast : public std::bad_cast
{
public:
   bad_any_cast(const std::type_info& any_type, const std::type_info& cast_type)
      : msg(getDemangledName(any_type) + "=>" + getDemangledName(cast_type))
   {
   }

   virtual const char * what() const throw()
   {
      return msg.c_str();
   }

   virtual ~bad_any_cast() throw() {}

   const std::string msg;
};

class empty_any_object: public std::bad_cast
{
public:
   virtual const char * what() const throw()
   {
      return "TESTNGPP::empty_any_object: "
                   "failed conversion using TESTNGPP::any_cast";
   }
};

template<typename ValueType>
ValueType * any_cast(any * operand)
{
   if(operand == 0) return 0;
   
   if(operand->empty())
      throw TESTNGPP_NS::empty_any_object();

   if(operand->type() != typeid(ValueType))
   {
      throw TESTNGPP_NS::bad_any_cast(typeid(ValueType), operand->type());
   }

   return &static_cast<any::holder<ValueType> *>(operand->content)->held;
}

template<typename ValueType>
inline const ValueType * any_cast(const any * operand)
{
   return any_cast<ValueType>(const_cast<any *>(operand));
}

template<typename ValueType>
ValueType any_cast(any & operand)
{
   typedef typename TESTNGPP_NS::TypeTraits<ValueType>::Type nonref;

   return *any_cast<nonref>(&operand);

#if 0
   nonref * result = any_cast<nonref>(&operand);
   if(!result)
      throw bad_any_cast();

   return *result;
#endif
}

template<typename ValueType>
inline ValueType any_cast(const any & operand)
{
   typedef typename TESTNGPP_NS::TypeTraits<ValueType>::Type nonref;

   return any_cast<const nonref &>(const_cast<any &>(operand));
}

TESTNGPP_NS_END

// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#endif

