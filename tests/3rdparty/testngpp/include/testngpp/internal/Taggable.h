#ifndef __TESTNGPP_TAGGABLE_H
#define __TESTNGPP_TAGGABLE_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
struct Taggable
{
   virtual
   unsigned int numberOfTags() const = 0;

   virtual
   const char** getTags() const = 0;

   virtual ~Taggable() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

