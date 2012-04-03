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

#ifndef __MOCKCPP_REPORT_FAILURE_H
#define __MOCKCPP_REPORT_FAILURE_H

#include <string>
#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

void
reportFailure
      ( unsigned int       line
      , const char*        file
      , const std::string& message);

#define MOCKCPP_REPORT_FAILURE(msg) \
   MOCKCPP_NS::reportFailure(__LINE__, __FILE__, msg)

#define MOCKCPP_ASSERT_FALSE(msg, expr) do {\
   if(expr) { \
      MOCKCPP_REPORT_FAILURE(msg); \
   } \
} while(0)

#define MOCKCPP_ASSERT_TRUE(msg, expr) do {\
   if(!(expr)) { \
      MOCKCPP_REPORT_FAILURE(msg); \
   } \
} while(0)

MOCKCPP_NS_END

#endif

