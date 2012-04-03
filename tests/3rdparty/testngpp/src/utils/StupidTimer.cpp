/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#if defined(_MSC_VER)
#include <windows.h>
#endif

#include <testngpp/utils/StupidTimer.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
namespace
{
#if defined(_MSC_VER)
int gettimeofday(struct timeval* tv, void*)
{
  union {
     long long ns100;
     FILETIME ft;
  } now;

  ::GetSystemTimeAsFileTime (&now.ft);
  tv->tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
  tv->tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
  return (0);
}
#endif

   timeval subtime(const timeval& end, const timeval& start)
   {
      timeval tv = end;
      while (tv.tv_usec < start.tv_usec)
      {
         tv.tv_usec += 1000000;
         tv.tv_sec--;
      }

      tv.tv_usec -= start.tv_usec;
      tv.tv_sec  -= start.tv_sec;

      return tv;
   }
}
////////////////////////////////////////////////////
StupidTimer::
StupidTimer()
{
   startTime.tv_sec  = 0;
   startTime.tv_usec = 0;
}

////////////////////////////////////////////////////
void
StupidTimer::
start()
{
    gettimeofday(&startTime, 0);
}

////////////////////////////////////////////////////
timeval
StupidTimer::
stop()
{
   timeval tv;
   gettimeofday(&tv, 0);

   return subtime(tv, startTime);
}

TESTNGPP_NS_END

