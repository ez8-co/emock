
#ifndef __TESTNGPP_STUPID_TIMER_H
#define __TESTNGPP_STUPID_TIMER_H

#if !defined(_MSC_VER)
#include <sys/time.h>
#endif

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

#if defined(_MSC_VER)
struct timeval
{
	unsigned int tv_sec;
	unsigned int tv_usec;
};
#endif

struct StupidTimer
{
   StupidTimer();

   void start();

   timeval stop();

private:

   timeval startTime;
};

TESTNGPP_NS_END

#endif

