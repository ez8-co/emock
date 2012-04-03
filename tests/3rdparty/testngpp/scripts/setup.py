from distutils.core import setup
import py2exe
options = {"py2exe": {"bundle_files": 1}}
setup(options = options,
    zipfile = None,
  console=["testngppgen.py"],)