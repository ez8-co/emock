/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>
                          <Chen Guodong: sinojelly@gmail.com>
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


#ifndef __MOCKCPP_UTILS_H
#define __MOCKCPP_UTILS_H

#include <mockcpp/mockcpp.h>
#include <exception>
#include <iostream>
#include <string>

MOCKCPP_NS_START

inline std::string getFileName(std::string file)
{
   if (file == "")
   {
	  return "NULL";
   }

   return file.substr(file.find_last_of("/\\")  + 1);
}

#define __RUN_NOTHROW(block) try block \
       catch (std::exception &e) \
       { \
           std::cout << "(" << getFileName(__FILE__) << ", " << __LINE__ << ") exception : " << e.what() << std::endl; \
       } \
       catch (...) \
       { \
           std::cout << "(" << getFileName(__FILE__) << ", " << __LINE__ << ") exception : Unknown" << std::endl; \
       }

#define __RUN_THROW(block) try block \
       catch (...) \
       { \
		   throw; \
       }

	   
MOCKCPP_NS_END

#endif
