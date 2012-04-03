#!/bin/bash
# build and install

# there is a $xunit_home/include/gtest/gtest.h
xunit_home=/usr/local

install_dir=/home/jelly/Programming/mockcpp-samples/mockcpp4gtest/mockcpp


function build() {
	mkdir $1 2>/dev/null
	cd $1
	cmake -DCMAKE_INSTALL_PREFIX=$install_dir -DMOCKCPP_XUNIT=gtest -DMOCKCPP_XUNIT_HOME=$xunit_home $2
	make install
}

build ../../build_mockcpp_to_install4gtest ../mockcpp/mockcpp

cd ../mockcpp/mockcpp
