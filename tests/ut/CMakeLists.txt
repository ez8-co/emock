CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE(FindPythonInterp)

IF(PYTHONINTERP_FOUND)
  SET(PYTHON ${PYTHON_EXECUTABLE})
ELSE(PYTHONINTERP_FOUND)
  MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(PYTHONINTERP_FOUND)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${PACKAGE_NAME}
    -DPACKAGE_STRING=${PACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
)

SET(UT_CASES
  TestAny.h
  TestChainableMockMethod.h
  TestChainableMockMethodContainer.h
  TestChainableMockMethodNameKey.h
  TestConstraintSet.h
  TestFormatter.h
  TestHolder.h
  TestIncrementStub.h
  TestInvocation.h
  TestInvocationMocker.h
  TestIsEqual.h
  TestIsStringContains.h
  TestIsStringEndWith.h
  TestIsStringStartWith.h
  TestMockObject.h
  TestReturnObjectList.h
  TestStringConstraint.h
  TestStubContainter.h
  TestCheck.h
  TestApiHook.h
  TestStaticMethodMocker.h
  TestNonvirtualMethodMocker.h
  TestEmockSample.h
  TestApiHookBase.h
  TestOverloadMethodMocker.h
  TestIgnoreReturnValue.h
)

IF(MSVC)
  SET(UT_CASES
  ${UT_CASES}
  TestApiHookStdcall.h
  )
ENDIF(MSVC)

IF(CMAKE_CL_64)
    ADD_DEFINITIONS(-DWIN64)
ENDIF(CMAKE_CL_64)

LINK_DIRECTORIES(
	${PROJECT_HOME}/build_emock/src/Debug
	${PROJECT_HOME}/build_testngpp/src/Debug
    ${PROJECT_HOME}/build_emock/src
    ${PROJECT_HOME}/build_testngpp/src)

IF(WIN32)
ELSE(WIN32)
LINK_DIRECTORIES(
	/usr/local/lib)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(BEFORE 
  .
  ${PROJECT_HOME}/include
  ${CMAKE_SOURCE_DIR}/3rdparty/testngpp/include
  )

SET(TEST_GENERATOR ${CMAKE_SOURCE_DIR}/3rdparty/testngpp/scripts/testngppgen.py)
SET(TESTCASE_PREFIX emock-ut)

IF(MSVC)
    ADD_DEFINITIONS(-DMSVC_VMG_ENABLED)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
ENDIF(MSVC)

IF(UNIX)
ADD_DEFINITIONS(
    -g -ggdb
)
ENDIF(UNIX)

IF(UNIX AND NOT CYGWIN)
ADD_DEFINITIONS(
    -fPIC
)
ENDIF(UNIX AND NOT CYGWIN)

FOREACH(CASE ${UT_CASES})
  GET_FILENAME_COMPONENT(CASE_NAME ${CASE} NAME_WE)
  SET(CASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${CASE_NAME}.cpp)

  ADD_CUSTOM_TARGET(${CASE_NAME} DEPENDS ${CASE_SRC})

  SET(CASE_MODULE ${TESTCASE_PREFIX}-${CASE_NAME})

  ADD_LIBRARY(${CASE_MODULE} MODULE ${CASE_SRC})

  TARGET_LINK_LIBRARIES(${CASE_MODULE}
    testngpp
    emock)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${CASE_SRC}
    COMMAND ${PYTHON} ${TEST_GENERATOR} -e gb2312 -o ${CASE_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CASE}
  )

  ADD_DEPENDENCIES(${CASE_MODULE} ${CASE_NAME})
ENDFOREACH()


