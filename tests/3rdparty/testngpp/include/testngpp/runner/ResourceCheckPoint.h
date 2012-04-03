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

#ifndef __TESTNGPP_RESOURCE_CHECK_POINT_H
#define __TESTNGPP_RESOURCE_CHECK_POINT_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

///////////////////////////////////////////////////////////
#if defined(TESTNGPP_DISABLE_RC) && TESTNGPP_DISABLE_RC

#define TESTNGPP_RCP int
#define TESTNGPP_SET_RESOURCE_CHECK_POINT() 0
#define TESTNGPP_VERIFY_RESOURCE_CHECK_POINT(rcp)
#define TESTNGPP_VERIFY_RCP_WITH_ERR_MSG(rcp) 

#else

struct ResourceCheckPoint
{
   size_t memory;
   unsigned int fds;
};

#define TESTNGPP_RCP TESTNGPP_NS::ResourceCheckPoint
///////////////////////////////////////////////////////////
ResourceCheckPoint testngppSetCheckPoint();
void testngppVerifyCheckPoint(const ResourceCheckPoint& rcp
        , const char*, unsigned int);

///////////////////////////////////////////////////////////
#define TESTNGPP_SET_RESOURCE_CHECK_POINT() \
   TESTNGPP_NS::testngppSetCheckPoint()

///////////////////////////////////////////////////////////
#define TESTNGPP_VERIFY_RESOURCE_CHECK_POINT(rcp) do { \
   TESTNGPP_NS::testngppVerifyCheckPoint(rcp, __FILE__, __LINE__); \
}while(0)

///////////////////////////////////////////////////////////
#define TESTNGPP_VERIFY_RCP_WITH_ERR_MSG(rcp) \
  try \
  { \
     TESTNGPP_VERIFY_RESOURCE_CHECK_POINT(rcp); \
  } \
  catch(std::exception& ex) \
  { \
      std::cerr << __FILE__ << "(" << __LINE__ << "):" \
                  << ex.what() << std::endl; \
  } 

#endif

TESTNGPP_NS_END

#endif

