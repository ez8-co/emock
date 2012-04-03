
INCLUDE(FindPythonInterp)

IF(PYTHONINTERP_FOUND)
  SET(PYTHON ${PYTHON_EXECUTABLE})
ELSE(PYTHONINTERP_FOUND)
  MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(PYTHONINTERP_FOUND)

IF(MSVC)
  SET(RM del)
ELSE(MSVC)
  SET(RM rm -rf)
ENDIF(MSVC)

SET(THIS_DIR ${CMAKE_SOURCE_DIR}/scripts)

ADD_CUSTOM_TARGET(compile-testngppgen ALL
   COMMAND ${PYTHON} ${THIS_DIR}/pycompile.py ${THIS_DIR}) 
   
ADD_CUSTOM_TARGET(cleanup-testngppgen
   COMMAND ${RM} ${THIS_DIR}/*.pyc ${THIS_DIR}/testngppgen/*.pyc)

SET(PYC_FILES 
  ${THIS_DIR}/testngppgen.pyc
  ${THIS_DIR}/testngppgen/AnnotationParser.pyc
  ${THIS_DIR}/testngppgen/ElemParser.pyc 
  ${THIS_DIR}/testngppgen/Fixture.pyc
  ${THIS_DIR}/testngppgen/FixtureParser.pyc
  ${THIS_DIR}/testngppgen/Generator.pyc
  ${THIS_DIR}/testngppgen/LogicalLine.pyc
  ${THIS_DIR}/testngppgen/Message.pyc
  ${THIS_DIR}/testngppgen/Name.pyc
  ${THIS_DIR}/testngppgen/Phase0.pyc
  ${THIS_DIR}/testngppgen/Phase1.pyc
  ${THIS_DIR}/testngppgen/Phase1Result.pyc
  ${THIS_DIR}/testngppgen/Phase2.pyc
  ${THIS_DIR}/testngppgen/Phase3.pyc
  ${THIS_DIR}/testngppgen/Phase4.pyc
  ${THIS_DIR}/testngppgen/PreprocessScope.pyc
  ${THIS_DIR}/testngppgen/PreprocessScopeParser.pyc
  ${THIS_DIR}/testngppgen/Process.pyc
  ${THIS_DIR}/testngppgen/TagsParser.pyc
  ${THIS_DIR}/testngppgen/TestCase.pyc
  ${THIS_DIR}/testngppgen/TestCaseParser.pyc
  ${THIS_DIR}/testngppgen/TestScope.pyc
  ${THIS_DIR}/testngppgen/Output.pyc
  ${THIS_DIR}/testngppgen/__init__.pyc)

FILE(REMOVE ${PYC_FILES})

INSTALL(DIRECTORY . DESTINATION testngpp/generator
       FILES_MATCHING PATTERN "*.pyc"
       PATTERN "CMakeFiles" EXCLUDE
       PATTERN ".svn" EXCLUDE
       PATTERN ".py" EXCLUDE)
