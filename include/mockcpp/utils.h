/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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
