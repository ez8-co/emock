
SET(EMOCK_SRC_ROOT ${CMAKE_SOURCE_DIR})

IF(NOT DEFINED EMOCK_XUNIT)
   SET(EMOCK_XUNIT STDEXCEPT)
ENDIF()

IF(EMOCK_NO_NAMESPACE)
   SET(EMOCK_NO_NAMESPACE 1)
ELSE(EMOCK_NO_NAMESPACE)
   SET(EMOCK_NO_NAMESPACE 0)
ENDIF(EMOCK_NO_NAMESPACE)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
    -DEMOCK_NO_NAMESPACE=${EMOCK_NO_NAMESPACE}
)

IF(MSVC)
    ADD_DEFINITIONS(-DMSVC_VMG_ENABLED) #  /Z7)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
ELSE(MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")
ENDIF(MSVC)

#IF(UNIX)
#MESSAGE("UNIX")
#ADD_DEFINITIONS(
#    -g -ggdb
#)
#ENDIF(UNIX)

IF(UNIX AND NOT CYGWIN)
ADD_DEFINITIONS(
    -fPIC
)
ENDIF(UNIX AND NOT CYGWIN)

IF(CMAKE_CL_64)
    ADD_DEFINITIONS(-DWIN64)
ENDIF(CMAKE_CL_64)

SET(EMOCK_SRCS 
    AfterMatcher.cpp
    AnyBase.cpp
    AnyCast.cpp
    Any.cpp
    Asserter.cpp
    AssertionFailedError.cpp
    BeforeMatcher.cpp
    CallerMatcher.cpp
    ChainableMockMethodContainer.cpp
    ChainableMockMethodCore.cpp
    ChainableMockMethodNameKey.cpp
    ChainableMockObjectBase.cpp
    ChainingMockHelper.cpp
    ConstraintSet.cpp
    DecoratedConstraint.cpp
    DefaultMatcher.cpp
    DefaultStub.cpp
    DieStub.cpp
    Exception.cpp
    ExpectsMatcher.cpp
    Formatter.cpp
    IdentityBuilder.cpp
    IgnoreResultHandler.cpp
    IgnoreResultHandlerFactory.cpp
    IgnoreReturnStub.cpp
    Ignore.cpp
    Invocation.cpp
    InvocationId.cpp
    InvocationMockBuilderGetter.cpp
    InvocationMocker.cpp
    InvocationMockerSet.cpp
    InvocationTimesMatcher.cpp
    InvokedAtLeast.cpp
    InvokedAtMost.cpp
    InvokedExactly.cpp
    InvokedOnce.cpp
    InvokedTimesMatcher.cpp
    IsAnythingHelper.cpp
    IsStringContains.cpp
    IsStringEndWith.cpp
    IsStringStartWith.cpp
    MismatchResultHandler.cpp
    MismatchResultHandlerFactory.cpp
    NormalResultHandler.cpp
    NormalResultHandlerFactory.cpp
    OutBoundPointer.cpp
    PendingMatcher.cpp
    ProcStub.cpp
    RefAny.cpp
    RepeatStub.cpp
    Result.cpp
    ReturnObjectList.cpp
    ReturnStub.cpp
    SimpleInvocationRecorder.cpp
    StringConstraint.cpp
    StubContainer.cpp
    StubsMatcher.cpp
    SymbolRetriever.cpp
    TestFailureMatcher.cpp
    ThenStub.cpp
    Trampoline.cpp
    TypelessConstraintAdapter.cpp
    TypelessStubAdapter.cpp
    TypeString.cpp
    VoidResultHandler.cpp
    VoidResultHandlerFactory.cpp
    WillStub.cpp
    HookMockObject.cpp
    ApiHookKey.cpp
    GlobalMockObject.cpp
    JmpOnlyApiHook.cpp
    JmpCode.cpp
    ApiHook.cpp

)

IF(${EMOCK_XUNIT} STREQUAL "GTEST" OR ${EMOCK_XUNIT} STREQUAL "gtest")

   IF(NOT DEFINED EMOCK_XUNIT_HOME)
      MESSAGE(FATAL_ERROR "Please specify EMOCK_XUNIT_HOME as the home path of googletest")
   ENDIF()
   FIND_FILE(GTEST_HEADER
             gtest.h 
             PATHS ${EMOCK_XUNIT_HOME}/include/gtest 
             NO_DEFAULT_PATH 
             NO_CMAKE_ENVIRONMENT_PATH 
             NO_CMAKE_PATH 
             NO_SYSTEM_ENVIRONMENT_PATH 
             NO_CMAKE_SYSTEM_PATH)
   IF(NOT GTEST_HEADER)
      MESSAGE(FATAL_ERROR "gtest.h not found in ${EMOCK_XUNIT_HOME}/include/gtest, please specify EMOCK_XUNIT_HOME as the home path of googletest correctly.")
   ENDIF()
   INCLUDE_DIRECTORIES(BEFORE ${EMOCK_XUNIT_HOME}/include)
   SET(EMOCK_SRCS ${EMOCK_SRCS} ports/failure/gtest_report_failure.cpp)

ELSEIF(${EMOCK_XUNIT} STREQUAL "CppUTest" OR ${EMOCK_XUNIT} STREQUAL "cpputest")

   IF(NOT DEFINED EMOCK_XUNIT_HOME)
      MESSAGE(FATAL_ERROR "Please specify EMOCK_XUNIT_HOME as the home path of googletest")
   ENDIF()
   FIND_FILE(CPPUTEST_HEADER
             TestHarness.h 
             PATHS ${EMOCK_XUNIT_HOME}/include/CppUTest
             NO_DEFAULT_PATH 
             NO_CMAKE_ENVIRONMENT_PATH 
             NO_CMAKE_PATH 
             NO_SYSTEM_ENVIRONMENT_PATH 
             NO_CMAKE_SYSTEM_PATH)
   IF(NOT CPPUTEST_HEADER)
      MESSAGE(FATAL_ERROR "TestHarness.h not found in ${EMOCK_XUNIT_HOME}/include/CppUTest, please specify EMOCK_XUNIT_HOME as the home path of CppUTest correctly.")
   ENDIF()
   INCLUDE_DIRECTORIES(BEFORE ${EMOCK_XUNIT_HOME}/include ${EMOCK_XUNIT_HOME}/include/Platforms/VisualCpp)
   SET(EMOCK_SRCS ${EMOCK_SRCS} ports/failure/cpputest_report_failure.cpp)   
   
ELSEIF(${EMOCK_XUNIT} STREQUAL "CPPUNIT" OR ${EMOCK_XUNIT} STREQUAL "cppunit")
   IF(NOT DEFINED EMOCK_XUNIT_HOME)
      MESSAGE(FATAL_ERROR "Please specify EMOCK_XUNIT_HOME as the home path of cppunit")
   ENDIF()
   FIND_FILE(CPPUNIT_HEADER Exception.h 
             PATHS ${EMOCK_XUNIT_HOME}/include/cppunit
             NO_DEFAULT_PATH 
             NO_CMAKE_ENVIRONMENT_PATH 
             NO_CMAKE_PATH 
             NO_SYSTEM_ENVIRONMENT_PATH 
             NO_CMAKE_SYSTEM_PATH)
   IF(NOT ${GTEST_HEADER})
      MESSAGE(FATAL_ERROR "Can't find file Exception.h, please specify EMOCK_XUNIT_HOME as the home path of cppunit correctly.")
   ENDIF()
   INCLUDE_DIRECTORIES(BEFORE ${EMOCK_XUNIT_HOME}/include)
   SET(EMOCK_SRCS ${EMOCK_SRCS} ports/failure/cppunit_report_failure.cpp)
ELSE()
   SET(EMOCK_SRCS ${EMOCK_SRCS} ports/failure/stdexcept_report_failure.cpp)
ENDIF()

IF(MSVC OR MINGW)
   SET(EMOCK_SRCS 
       ${EMOCK_SRCS} 
       WinCodeModifier.cpp
   )
ELSE()
   SET(EMOCK_SRCS 
       ${EMOCK_SRCS} 
       UnixCodeModifier.cpp
   )
ENDIF()
######################################################
SET(EMOCK_HEADERS_PATH ${EMOCK_SRC_ROOT}/include/emock)

######################################################
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/tests/3rdparty/testngpp/src)

ADD_LIBRARY(emock STATIC ${EMOCK_SRCS})

IF(MINGW)
   TARGET_LINK_LIBRARIES(emock Dbghelp)
ENDIF()

INCLUDE_DIRECTORIES(BEFORE ${EMOCK_SRC_ROOT}/include)

INSTALL(
   TARGETS emock
   ARCHIVE DESTINATION lib)

IF(MSVC OR MINGW)
INSTALL(
   FILES ${CMAKE_BINARY_DIR}/src/Debug/emock.pdb
   DESTINATION lib)
ENDIF()
