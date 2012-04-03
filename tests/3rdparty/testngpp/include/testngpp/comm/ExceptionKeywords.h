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

#ifndef __CPPTEST_EXCEPTION_KEYWORDS_H
#define __CPPTEST_EXCEPTION_KEYWORDS_H

#include <testngpp/testngpp.h>


TESTNGPP_NS_START

struct Success {};

#define __TESTNGPP_TRY       try { try { 
#define __TESTNGPP_CATCH(ex) throw TESTNGPP_NS::Success(); }  catch(ex) { 
#define __TESTNGPP_CATCH_ALL throw TESTNGPP_NS::Success(); }  catch(TESTNGPP_NS::Success&){throw;} catch(...) { 
#define __TESTNGPP_FINALLY   throw TESTNGPP_NS::Success(); }} catch(...) { 
#define __TESTNGPP_DONE      try {throw;}catch(TESTNGPP_NS::Success&){}} 

#define __TESTNGPP_DO        try {
#define __TESTNGPP_CLEANUP   throw TESTNGPP_NS::Success(); } catch(...) {
//#define __TESTNGPP_DONE    try {throw;}catch(TESTNGPP_NS::Success&){}} 

//#define __TESTNGPP_TRY       try { try { 
//#define __TESTNGPP_CATCH(ex) throw TESTNGPP_NS::Success(); }  catch(ex) { 
#define __TESTNGPP_END_TRY   throw TESTNGPP_NS::Success(); }} catch(TESTNGPP_NS::Success&) {}

TESTNGPP_NS_END

#endif

