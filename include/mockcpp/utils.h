

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
