
#ifndef __MOCKCPP_MOKC_H
#define __MOCKCPP_MOKC_H

#ifdef __cplusplus
#  include <mockcpp/ChainingMockHelper.h>
#  include <mockcpp/ProcStub.h>

#  if defined(MOCKCPP_USE_MOCKABLE) 
#    include <mockcpp/Functor.h>
#    define MOCKER(api) MOCKCPP_NS::GlobalMockObject::instance.method(#api)
#  else
#    include <mockcpp/ApiHookMocker.h>
#    define MOCKER(api) MOCKCPP_NS::mockAPI(#api, api)
#  endif

USING_MOCKCPP_NS

#endif

#endif

