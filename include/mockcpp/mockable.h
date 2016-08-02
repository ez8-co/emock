
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
