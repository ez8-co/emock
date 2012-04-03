
#ifndef __TESTNGPP_ENVIRONMENT_CLEANER_H
#define __TESTNGPP_ENVIRONMENT_CLEANER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct EnvironmentCleaner
{
   virtual void cleanUp() = 0;

   virtual ~EnvironmentCleaner() {}
};

TESTNGPP_NS_END

#endif
