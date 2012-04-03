
IF(MSVC)
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
ENDIF(MSVC)

IF(NOT DEFINED TESTNGPP_DISABLE_RC)
  SET(TESTNGPP_DISABLE_RC FALSE)
ENDIF(NOT DEFINED TESTNGPP_DISABLE_RC)

IF(NOT DEFINED TESTNGPP_DISABLE_SANDBOX)
  SET(TESTNGPP_DISABLE_SANDBOX FALSE)
ENDIF(NOT DEFINED TESTNGPP_DISABLE_SANDBOX)

IF(TESTNGPP_DISABLE_SANDBOX)
  ADD_DEFINITIONS(-DTESTNGPP_DISABLE_SANDBOX=1)
ELSE(TESTNGPP_DISABLE_SANDBOX)
  ADD_DEFINITIONS(-DTESTNGPP_DISABLE_SANDBOX=0)
ENDIF(TESTNGPP_DISABLE_SANDBOX)

IF(TESTNGPP_DISABLE_RC)
  ADD_DEFINITIONS(-DTESTNGPP_DISABLE_RC=1)
ELSE(TESTNGPP_DISABLE_RC)
  ADD_DEFINITIONS(-DTESTNGPP_DISABLE_RC=0)
ENDIF(TESTNGPP_DISABLE_RC)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

SET(TESTNGPP_LIBRARY testngpp testngpp-utils)

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include)
ADD_DEFINITIONS(-D__STDC_FORMAT_MACROS)

IF (MSVC)
    INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include/msinttypes)
	INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/3rdparty/msinttypes)
ENDIF()

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/src/utils)

SET(RC_SRCS ResourceCheckPoint.cpp)

SET(SANDBOX_SRCS
  sandbox/TestCaseSandboxResultReporter.cpp 
  sandbox/TestCaseSandboxResultDecoder.cpp 
  sandbox/Sandbox.cpp 
  sandbox/SandboxProcessor.cpp 
  sandbox/TestCaseSandboxHandler.cpp 
  sandbox/TestCaseSandbox.cpp 
  sandbox/TestHierarchySandboxRunner.cpp 

  utils/PipeReadableChannel.cpp 
  utils/PipeWrittableChannel.cpp  
)

SET(WIN32_SANDBOX_SRCS
   sandbox/TestCaseSandboxResultReporter.cpp 
   sandbox/TestCaseSandboxResultDecoder.cpp  
   win32/Win32PipeWrittableChannel.cpp
   win32/Win32PipeReadableChannel.cpp
   win32/GetLastError.cpp
   win32/Win32TestHierarchySandboxRunner.cpp
   win32/Win32Sandbox.cpp
   win32/Win32TestCaseSandbox.cpp
)

SET(TESTNGRUNNER_LIB_SRCS
  runners/TestSuiteRunner.cpp 
  runners/SimpleTestCaseRunner.cpp 
  runners/TestFixtureRunner.cpp 
  runners/TestFixtureRunnerFactory.cpp 
  runners/SimpleTestHierarchyRunner.cpp 
  runners/TestCaseHierarchy.cpp
  runners/TestHierarchyHandler.cpp
  runners/TestSuiteContext.cpp
  runners/TestFixtureContext.cpp
  runners/TestRunnerContext.cpp
  runners/TestCaseRunnerFactory.cpp

  loaders/ModuleTestSuiteLoader.cpp 
  loaders/ModuleTestSuiteLoaderFactory.cpp 
  loaders/ModuleTestListenerLoader.cpp 
  loaders/ModuleTestListenerLoaderFactory.cpp 

  reports/SimpleTestResultDispatcher.cpp 
  reports/SimpleTestResultReporter.cpp 
  reports/SimpleTestCaseResultReporter.cpp 
  reports/SmartTestCaseResultCollector.cpp 
  reports/SimpleTestSuiteResultReporter.cpp
  reports/SimpleTestResultManager.cpp

  filters/WildcardTestFilter.cpp 
  filters/OrCompositeTestFilter.cpp 
  filters/GeneralTestFilter.cpp 
  filters/TestFilterFactory.cpp 
  filters/PosixFNMatcher.cpp 

  tags/AndCompositeTaggableFilter.cpp 
  tags/OrCompositeTaggableFilter.cpp 
  tags/NotCompositeTaggableFilter.cpp 
  tags/GeneralTagsFilter.cpp 
  tags/EmptyTagsFilter.cpp 
  tags/MatchAllTagsFilter.cpp 
  tags/TagsFilters.cpp 
  tags/TagsParser.cpp 
  tags/FixtureTagsFilter.cpp

  TestRunner.cpp
)

IF(NOT TESTNGPP_DISABLE_RC)
   SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS} ${RC_SRCS})
ENDIF(NOT TESTNGPP_DISABLE_RC)

IF(NOT TESTNGPP_DISABLE_SANDBOX)
   IF(MSVC)
      SET(TESTNGRUNNER_LIB_SRCS
         ${TESTNGRUNNER_LIB_SRCS}
         ${WIN32_SANDBOX_SRCS}
      )
   ELSE(MSVC)
      SET(TESTNGRUNNER_LIB_SRCS
         ${TESTNGRUNNER_LIB_SRCS}
         ${SANDBOX_SRCS}
      )
   ENDIF(MSVC)
ENDIF(NOT TESTNGPP_DISABLE_SANDBOX)

IF(MSVC)
  SET(TESTNGRUNNER_LIB_SRCS
     ${TESTNGRUNNER_LIB_SRCS}
     filters/Win32Fnmatch.c
  )
ENDIF(MSVC)

IF(TESTNGPP_USE_DLOPEN)
  SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS}
      loaders/DLModuleLoader.cpp 
      loaders/DLModuleLoaderFactory.cpp
  )
ELSEIF(TESTNGPP_USE_LTDL)
  SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS}
      loaders/LTModuleLoader.cpp 
      loaders/LTModuleLoaderFactory.cpp
  )
ELSEIF(TESTNGPP_USE_LOADLIBRARY)
  SET(TESTNGRUNNER_LIB_SRCS ${TESTNGRUNNER_LIB_SRCS}
      loaders/Win32DllModuleLoader.cpp 
      loaders/Win32DllModuleLoaderFactory.cpp
  )
ELSE(TESTNGPP_USE_DLOPEN)
  MESSAGE(FATAL_ERROR "No module loader found")
ENDIF(TESTNGPP_USE_DLOPEN)

IF(UNIX)
ADD_DEFINITIONS(
    -g -ggdb
)
ENDIF(UNIX)

ADD_LIBRARY(testngpp-runner-lib STATIC ${TESTNGRUNNER_LIB_SRCS})

TARGET_LINK_LIBRARIES(testngpp-runner-lib ${TESTNGPP_LIBRARY})

ADD_EXECUTABLE(testngpp-runner TestRunnerMain.cpp) 

IF(MSVC)
   ADD_EXECUTABLE(testngpp-win32-testcase-runner win32/TestCaseSandboxRunnerMain.cpp)
   TARGET_LINK_LIBRARIES(testngpp-win32-testcase-runner ${TESTNGPP_LIBRARY} testngpp-runner-lib)

   INSTALL(TARGETS testngpp-win32-testcase-runner
      RUNTIME DESTINATION bin)
ENDIF(MSVC)

# -Wl,--export-dynamic
ADD_DEPENDENCIES(testngpp-runner testngpp-runner-lib)
TARGET_LINK_LIBRARIES(testngpp-runner ${TESTNGPP_LIBRARY} testngpp-runner-lib)

IF(TESTNGPP_USE_DLOPEN)
  TARGET_LINK_LIBRARIES(testngpp-runner-lib dl)
ELSEIF(TESTNGPP_USE_LTDL)
  TARGET_LINK_LIBRARIES(testngpp-runner-lib ltdl)
ELSEIF(TESTNGPP_USE_LOADLIBRARY)
ELSE(TESTNGPP_USE_DLOPEN)
  MESSAGE(FATAL_ERROR "No module loader found")
ENDIF(TESTNGPP_USE_DLOPEN)

INSTALL(
   TARGETS testngpp-runner
   RUNTIME DESTINATION bin)

