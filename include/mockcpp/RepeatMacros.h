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

#ifndef __MOCKCPP_REPEAT_MACROS_H
#define __MOCKCPP_REPEAT_MACROS_H

#define REPEAT_0(macro) 
#define REPEAT_1(macro) REPEAT_0(macro)
#define REPEAT_2(macro) REPEAT_1(macro) macro(1)
#define REPEAT_3(macro) REPEAT_2(macro) macro(2)
#define REPEAT_4(macro) REPEAT_3(macro) macro(3)
#define REPEAT_5(macro) REPEAT_4(macro) macro(4)
#define REPEAT_6(macro) REPEAT_5(macro) macro(5)
#define REPEAT_7(macro) REPEAT_6(macro) macro(6)
#define REPEAT_8(macro) REPEAT_7(macro) macro(7)
#define REPEAT_9(macro) REPEAT_8(macro) macro(8)
#define REPEAT_10(macro) REPEAT_9(macro) macro(9)
#define REPEAT_11(macro) REPEAT_10(macro) macro(10)
#define REPEAT_12(macro) REPEAT_11(macro) macro(11)
#define REPEAT_13(macro) REPEAT_12(macro) macro(12)
#define REPEAT_14(macro) REPEAT_13(macro) macro(13)
#define REPEAT_15(macro) REPEAT_14(macro) macro(14)
#define REPEAT_16(macro) REPEAT_15(macro) macro(15)
#define REPEAT_17(macro) REPEAT_16(macro) macro(16)
#define REPEAT_18(macro) REPEAT_17(macro) macro(17)
#define REPEAT_19(macro) REPEAT_18(macro) macro(18)
#define REPEAT_20(macro) REPEAT_19(macro) macro(19)

#define END_MACRO_0(macro) 
#define END_MACRO_1(macro) macro(1)
#define END_MACRO_2(macro) macro(2)
#define END_MACRO_3(macro) macro(3)
#define END_MACRO_4(macro) macro(4)
#define END_MACRO_5(macro) macro(5)
#define END_MACRO_6(macro) macro(6)
#define END_MACRO_7(macro) macro(7)
#define END_MACRO_8(macro) macro(8)
#define END_MACRO_9(macro) macro(9)
#define END_MACRO_10(macro) macro(10)
#define END_MACRO_11(macro) macro(11)
#define END_MACRO_12(macro) macro(12)
#define END_MACRO_13(macro) macro(13)
#define END_MACRO_14(macro) macro(14)
#define END_MACRO_15(macro) macro(15)
#define END_MACRO_16(macro) macro(16)
#define END_MACRO_17(macro) macro(17)
#define END_MACRO_18(macro) macro(18)
#define END_MACRO_19(macro) macro(19)
#define END_MACRO_20(macro) macro(20)

#define REPEAT(n, macro, end_macro) REPEAT_##n (macro) END_MACRO_##n(end_macro)
#define SIMPLE_REPEAT(n, macro) REPEAT(n, macro, macro)

#endif

