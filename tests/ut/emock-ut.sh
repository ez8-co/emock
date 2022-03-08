#!/bin/bash

TESTNGPP_ROOT=`pwd`/../3rdparty/testngpp

EMOCK_UT_SUITES=`ls ./libemock-ut-*`
${TESTNGPP_ROOT}/src/runner/testngpp-runner \
   -L${TESTNGPP_ROOT}/src/listeners \
   -l"testngppxmllistener result.xml" \
   -l"testngppstdoutlistener -c " \
   -t"* > ft" -c100 $@ \
   ${EMOCK_UT_SUITES}

