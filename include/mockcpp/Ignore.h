
#ifndef __MOCKCPP_IGNORE_H
#define __MOCKCPP_IGNORE_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct Ignore
{
   bool operator==(const Ignore& rhs) const
   {
      return true;
   }
};

struct Any;

Any& getIgnore();

MOCKCPP_NS_END

#endif

