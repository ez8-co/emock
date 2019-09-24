
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(emock)

ADD_SUBDIRECTORY(src)

INSTALL(DIRECTORY include/emock DESTINATION include
        PATTERN ".svn" EXCLUDE)

SET(EMOCK_XUNIT "testngpp" CACHE STRING "Set to gtest/cpputest/cppunit to use other testframeworks.")


