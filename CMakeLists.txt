
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(mockcpp)

INCLUDE(ProjectVar.txt)

ADD_SUBDIRECTORY(src)

INSTALL(DIRECTORY include/mockcpp DESTINATION include
        PATTERN ".svn" EXCLUDE)

IF(MOCKCPP_INSTALL_BOOST)
  IF(MSVC)
    INSTALL(DIRECTORY 3rdparty/boost DESTINATION 3rdparty
            PATTERN ".svn" EXCLUDE)
  ELSE(MSVC)
    INSTALL(DIRECTORY 3rdparty/boost DESTINATION include
            PATTERN ".svn" EXCLUDE)
  ENDIF()
ENDIF()

SET(MOCKCPP_XUNIT "testngpp" CACHE STRING "Set to gtest/cpputest/cppunit to use other testframeworks.")


