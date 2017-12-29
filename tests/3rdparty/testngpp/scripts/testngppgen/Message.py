
import sys
import os

from testngppgen.Phase1Result import *

####################################################################
def message(file, line_number, type, msg):
   return os.path.basename(file) + ":" + str(line_number) + ": " + type + ": " + msg

####################################################################
def raw_fatal(file, line_number, error):
   print(message(file, line_number, "error", error), sys.stderr)
   sys.exit(1)

####################################################################
def fatal(file, line, error):
   raw_fatal(file, line.get_line_number(), error)

####################################################################
def warning(file, line, msg):
   print(message(file, line.get_line_number(), "warning", msg), sys.stderr)

####################################################################
def info(file, line, msg):
   print(message(file, line.get_line_number(), "info", msg))

####################################################################
def report_expect_char(file, line, expected_char, unexpected_char):
      fatal(file, line, "expects char '" + expected_char + \
         "', but \'" + unexpected_char + "\' found")

####################################################################
