
IF(MSVC)
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
ENDIF(MSVC)

SET(TESTNGPP_SRCS
  bool_array.cpp       
  mem_pool_base.cpp
  debug_new.cpp        
  static_mem_pool.cpp
  interface_4xunit.cpp
  reporter.cpp
  check_status.cpp
  NoThrowsReporter.cpp
)

# include debug info in testngpp.lib
IF(MSVC)
	ADD_DEFINITIONS( /Z7 )
ENDIF(MSVC)

IF(UNIX AND NOT CYGWIN)
ADD_DEFINITIONS(
    -fPIC
)
ENDIF(UNIX AND NOT CYGWIN)

ADD_LIBRARY(mem-checker STATIC ${TESTNGPP_SRCS})

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty)


