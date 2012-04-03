
#include <limits>
#include <mockcpp/types/AnyCast.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
template <typename ValueType>
ValueType* type_any_cast(AnyBase* op)
{
   return 0;
}

///////////////////////////////////////////////////////
template <typename Unsigned, typename Signed, typename BaseType>
Unsigned* unsigned_type_any_cast(AnyBase* op)
{
   Unsigned *p = 0;
   if((p = __any_cast<Unsigned>(op)) ||
      (p = (Unsigned*)type_any_cast<BaseType>(op))
   )
   {
      return p;
   }

   Signed* ps = 0;
   if((ps = __any_cast<Signed>(op)) && (*ps) > 0)
   {
      return (Unsigned*)ps;
   }

   return 0;
}

///////////////////////////////////////////////////////
template <typename Signed, typename BaseType >
Signed* signed_type_any_cast(AnyBase* op)
{
   Signed *p = 0;

   (p = __any_cast<Signed>(op)) ||
   (p = (Signed*)type_any_cast<BaseType>(op));

   return p;
}

///////////////////////////////////////////////////////
template <>
char* type_any_cast<char>(AnyBase* op)
{
   return signed_type_any_cast<char, void>(op);
}

///////////////////////////////////////////////////////
template <>
short* type_any_cast<short>(AnyBase* op)
{
   return signed_type_any_cast<short, char>(op);
}

///////////////////////////////////////////////////////
template <>
int* type_any_cast<int>(AnyBase* op)
{
   return signed_type_any_cast<int, short>(op);
}

///////////////////////////////////////////////////////
template <>
long* type_any_cast<long>(AnyBase* op)
{
   return signed_type_any_cast<long, int>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned char* type_any_cast<unsigned char>(AnyBase* op)
{
   return unsigned_type_any_cast<unsigned char, char, void>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned short* type_any_cast<unsigned short>(AnyBase* op)
{
   return unsigned_type_any_cast<unsigned short, short, unsigned char>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned int* type_any_cast<unsigned int>(AnyBase* op)
{
   return unsigned_type_any_cast<unsigned int, int, unsigned short>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned long* type_any_cast<unsigned long>(AnyBase* op)
{
   return unsigned_type_any_cast<unsigned long, long, unsigned int>(op);
}

///////////////////////////////////////////////////////
template <typename ValueType>
ValueType* scope_check_any_cast(AnyBase* op)
{
   ValueType* v = type_any_cast<ValueType>(op);
   if(v != 0)
   {
      return v;
   }

   unsigned long* ul = type_any_cast<unsigned long>(op);
   if(ul  && ((*ul) <= (unsigned long)std::numeric_limits<ValueType>::max()))
   {
      return (ValueType*)ul;
   }

   long* l = type_any_cast<long>(op);
   if(l  && (((*l) <= (long)std::numeric_limits<ValueType>::max()) && 
              (*l) >= (long)std::numeric_limits<ValueType>::min()))
   {
      return (ValueType*)l;
   }

   return 0;
}

///////////////////////////////////////////////////////
template <>
char* any_cast<char>(AnyBase* op)
{
   return scope_check_any_cast<char>(op);
}

///////////////////////////////////////////////////////
template <>
short* any_cast<short>(AnyBase* op)
{
   return scope_check_any_cast<short>(op);
}

///////////////////////////////////////////////////////
template <>
int* any_cast<int>(AnyBase* op)
{
   return scope_check_any_cast<int>(op);
}

///////////////////////////////////////////////////////
template <>
long* any_cast<long>(AnyBase* op)
{
   return scope_check_any_cast<long>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned char* any_cast<unsigned char>(AnyBase* op)
{
   return scope_check_any_cast<unsigned char>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned short* any_cast<unsigned short>(AnyBase* op)
{
   return scope_check_any_cast<unsigned short>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned int* any_cast<unsigned int>(AnyBase* op)
{
   return scope_check_any_cast<unsigned int>(op);
}

///////////////////////////////////////////////////////
template <>
unsigned long* any_cast<unsigned long>(AnyBase* op)
{
   return scope_check_any_cast<unsigned long>(op);
}

MOCKCPP_NS_END

