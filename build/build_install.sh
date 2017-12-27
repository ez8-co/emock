#!/bin/bash
# build and install

install_dir=/home/jelly/Programming/cpp-ut-project/cpp-ut-project/tools/mockcpp

function build() {
	mkdir $1 2>/dev/null
	cd $1
	cmake -DCMAKE_INSTALL_PREFIX=$install_dir $2
	make install
}

build ../../build_mockcpp_to_install ../mockcpp/mockcpp

cd ../mockcpp/mockcpp

