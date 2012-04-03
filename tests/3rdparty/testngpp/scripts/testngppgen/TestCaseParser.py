#!/usr/bin/python

from Phase1Result import *
from TestCase import *
from PreprocessScope import *

from Message import *

##########################################################
class TestCaseParser:
   #######################################################
   def __init__(self, name, scope, file, line, annotations):
      self.begin = True
      self.done = None
      self.numberOfUnclosedBraces = 0
      self.file = file
      self.__verify_testcase_annotations(annotations)
      self.testcase = TestCase(name, scope, file, line, annotations)
      self.parse_line(Unknown(line, name[3]))

   #######################################################
   def should_parse_sub_scopes(self):
      return False

   #######################################################
   def verify_scope(self, scope):
      return False

   #######################################################
   def __verify_testcase_annotations(self, annotations):
      for anno in annotations:
         if anno.get_tag() not in ["test"]:
            warning(self.file, anno, "unknown annotation @" + anno.get_tag())

   #######################################################
   def get_container(self):
      return None

   #######################################################
   def get_elem_parser(self, scope, file, line):
      return None

   #######################################################
   def __handle_space(self, line, c):
      if c.isspace():
         return True

      return None
      
   #######################################################
   def __handle_done(self, line, c):
      if not self.done:
         return None

      fatal(self.file, line, "unexpected char '" + c + "' in test case definition")
      
   #######################################################
   def __handle_begin(self, line, c):
      if not self.begin:
         return None

      if c == '{':
         self.numberOfUnclosedBraces = 1
         self.begin = None
         return True

      report_expect_char(self.file, line, "{", c)
  
   #######################################################
   def __handle_others(self, line, c):
      if c == '{':
         self.numberOfUnclosedBraces += 1
      elif c == '}':
         self.numberOfUnclosedBraces -= 1
         if self.numberOfUnclosedBraces == 0:
            self.done = True
      
   #######################################################
   def handle_char(self, line, c):
      self.__handle_space(line, c) or \
      self.__handle_done(line, c) or \
      self.__handle_begin(line, c) or \
      self.__handle_others(line, c)

   #######################################################
   def is_done(self):
      if self.done: return self.testcase
      return None

   #######################################################
   def parse_line(self, line):
      if self.done:
         fatal(self.file, line, "internal error while parsing in test case")

      for c in line.get_content():
         self.handle_char(line, c)

      return self.is_done()

   #######################################################
   def handle_tag(self, tag):
      warning(self.file, tag, "annotation is not allowed in testcase definition")

##########################################################
