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

