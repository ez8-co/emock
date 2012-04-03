#!/usr/bin/python

import sys
import py_compile
import compileall

if __name__ == '__main__':
   path = sys.argv[1]
   file = path + '/testngppgen.py'
   package = path + '/testngppgen'
   py_compile.compile(file)
   compileall.compile_dir(package, 0)
