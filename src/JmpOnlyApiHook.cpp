***/

#include <string.h>

#include "JmpOnlyApiHook.h"
#include <mockcpp/JmpCode.h>
#include <mockcpp/CodeModifier.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
struct JmpOnlyApiHookImpl
{
   /////////////////////////////////////////////////////
   JmpOnlyApiHookImpl
              ( const void* api
              , const void* stub)
		: m_jmpCode(api, stub)
        , m_originalData(0)
        , m_api(api)
   {
      startHook();
   }

   /////////////////////////////////////////////////////
   ~JmpOnlyApiHookImpl()
   {
      stopHook();
   }

   /////////////////////////////////////////////////////
   void saveOriginalData()
   {
      m_originalData = new char[m_jmpCode.getCodeSize()];
      ::memcpy(m_originalData, m_api, m_jmpCode.getCodeSize());
   }

   /////////////////////////////////////////////////////
   void startHook()
   {
      saveOriginalData();
      changeCode(m_jmpCode.getCodeData());
   }

   /////////////////////////////////////////////////////
   void stopHook()
   {
      changeCode(m_originalData);
      delete [] m_originalData;
   }

   /////////////////////////////////////////////////////
   void changeCode(const void* data)
   {
      CodeModifier::modify(const_cast<void*>(m_api), data, m_jmpCode.getCodeSize());
   }

   /////////////////////////////////////////////////////
   JmpCode m_jmpCode;
   char* m_originalData;
   const void* m_api;
};

/////////////////////////////////////////////////////////////////
JmpOnlyApiHook::JmpOnlyApiHook 
              ( const void* api 
              , const void* stub )
	: This(new JmpOnlyApiHookImpl(api, stub))
{
}

/////////////////////////////////////////////////////////////////
JmpOnlyApiHook::~JmpOnlyApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

