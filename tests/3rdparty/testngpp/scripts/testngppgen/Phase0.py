#!/usr/bin/python

import sys

from LogicalLine import *
from Message import raw_fatal

#######################################################
class Phase0Parser:
   def __init__(self, file, lines):
      self.file  = file
      self.lines = lines
      self.logical_lines = []
      self.line_number = 1
      self.working_line = None

   def close_working_line(self):
      if not self.working_line:
         return 

      self.logical_lines.append(self.working_line)
      self.working_line = None

   def add_unclosed_line(self, line):
      if self.working_line:
         self.working_line.add_line(line)
         return

      self.working_line = LogicalLine(line, self.line_number)
     
   def add_closed_line(self, line):
      if self.working_line:
         self.working_line.add_line(line)
      else:
         self.working_line = LogicalLine(line, self.line_number)
      
      self.close_working_line()

   def parse_line(self, line):
      if len(line) == 0:
         self.close_working_line()
         return

      if line[-1] == "\\":
         if len(line) > 1 and line[-2] == "\\":
            raw_fatal(self.file, self.line_number, "stray '\\' in program")
         else:
            self.add_unclosed_line(line)
      else:
         self.add_closed_line(line)

   def parse(self):
      for line in self.lines:
         self.parse_line(line)
         self.line_number += 1

      return self.logical_lines

##########################################################
def phase0(file, lines):
   return Phase0Parser(file, lines).parse()


