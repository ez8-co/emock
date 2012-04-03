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

#ifndef __MOCKCPP_MOCKABLE_H
#define __MOCKCPP_MOCKABLE_H

#if defined(__cplusplus) && defined(MOCKCPP_USE_MOCKABLE)
#  include <mockcpp/Functor.h>
#  include <boost/typeof/typeof.hpp>
#  define MOCKABLE(function) MOCKER(function).defaults().will(invoke(function)); \
                             MOCKCPP_NS::Functor<BOOST_TYPEOF(function)> function(#function, __FUNCTION__)
#  define MCALL(function) MOCKCPP_NS::Functor<BOOST_TYPEOF(function)>(#function, __FUNCTION__) 
#else
#  define MOCKABLE(function)
#  define MCALL(function) function
#endif

#endif
