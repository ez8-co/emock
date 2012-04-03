#!/usr/bin/python

import sys
import re
import os
import codecs

from Phase1Result import *

from PreprocessScope import *
from Fixture import Fixture

from TestCaseParser import TestCaseParser
from PreprocessScopeParser import *
from ClassDeclParser import ClassDeclParser
from DataProviderParser import DataProviderParser

from Message import *

##########################################################

testcase_re1 = re.compile( r'^\s*TEST\s*\(\s*(?P<testcaseName>.+)\s*\)\s*$', re.UNICODE)
testcase_re2 = re.compile( r'^\s*void\s+(?P<testcaseId>test[A-Za-z0-9_]+)\s*\(\s*(void)?\s*\)\s*(?P<rest>.*)\s*$')
testcase_re3 = re.compile( r'^\s*void\s+(?P<testcaseId>[A-Za-z_][A-Za-z0-9_]*)\s*\(\s*(void)?\s*\)\s*(?P<rest>.*)\s*$')

p_testcase_re1 = re.compile( r'^\s*PTEST\s*\(\s*.+\)\s*,\s*(?P<testcaseName>.+)\s*\)\s*$', re.UNICODE)

class_decl_re = re.compile(r'^\s*(struct|class)\s+[A-Za-z0-9_]+\s*(?P<rest>.*)$')

data_provider_re = re.compile(r'^\s*DATA_PROVIDER\s*\(\s*(?P<name>[A-Za-z0-9_]+)\s*,\s*(?P<items>[1-9][0-9]*)(?P<rest>(.*))\s*$')

##########################################################
def is_testcase_def(line):
   matched = testcase_re1.match(line) 
   if matched:
      return None, matched.group("testcaseName"), None, ""

   matched = testcase_re2.match(line)
   if matched:
      return matched.group("testcaseId"), None, None, matched.group("rest") 

   matched = p_testcase_re1.match(line) 
   if matched:
      return None, matched.group("testcaseName"), True, ""

   return None

##########################################################
def is_data_provider(line):
   matched = data_provider_re.match(line)
   if matched:
      return matched.group("name"), matched.group("items"), matched.group("rest")
  
   return None

##########################################################
def is_class_decl(line):
   matched = class_decl_re.match(line)
   if matched:
     return matched.group("rest")

   return None

##########################################################
def might_be_testcase_def(line):
   matched = testcase_re3.match(line)
   if matched:
      return matched.group("testcaseId"), None, None, matched.group("rest")

   return None
   
##########################################################
class FixtureParser:
   def __init__(self, name, file, line, annotations):
      self.numberOfUnclosedBraces = 0
      self.begin = True
      self.end = None
      self.done = None
      self.file = file
      self.line = line
      self.annotations = []

      self.container = Fixture(name, self.file, self.line, annotations)

   #######################################################
   def get_container(self):
      return self.container

   #######################################################
   def __might_be_elem_def(self, content):
      return might_be_testcase_def(content)
   
   #######################################################
   def __has_test_annotation(self):
      for anno in self.annotations:
         if anno.get_tag() in ["test"] : return True

      return False

   #######################################################
   def __is_testcase_def(self, line):
      id = self.__might_be_elem_def(line.get_content())
      if id and self.__has_test_annotation():
         return id

      return is_testcase_def(line.get_content())

   #######################################################
   def should_parse_sub_scopes(self):
      return True

  #######################################################
   def __verify_dup_annotation(self, annotation):
      for anno in self.annotations:
         if annotations.get_tag() == anno:
            fatal(self.line, annotation, "duplicated annotation @" + annotation.get_tag())

   #######################################################
   def handle_tag(self, annotation):
      self.__verify_dup_annotation(annotation)
      self.annotations.append(annotation)

   #######################################################
   def __report_useless_annotations(self):
      for anno in self.annotations:
         warning(self.file, anno, "useless annotation @" + anno.get_tag())

      self.annotations = []

   #######################################################
   def verify_scope(self, tag):
      self.__report_useless_annotations()
      return True

   #######################################################
   def get_elem_parser(self, container, file, line):
      testcase = self.__is_testcase_def(line)
      if testcase != None:
         return self.__create_testcase_parser(testcase, container.get_scope(), file, line.get_line_number())

      rest = is_class_decl(line.get_content())
      if rest != None:
         return self.__create_class_decl_parser(rest, file, line.get_line_number())
      
      data_provider = is_data_provider(line.get_content())
      if data_provider != None:
         return DataProviderParser(data_provider, file, line.get_line_number())

      return None
         
   #######################################################
   def __create_class_decl_parser(self, content, file, line):
      return ClassDeclParser(content, file, line)

   #######################################################
   def __create_testcase_parser(self, elem_name, scope, file, line):
      parser = TestCaseParser(elem_name, scope, file, line, self.annotations)
      self.annotations = []
      return parser

   #######################################################
   def get_type_name(self):
      return "fixture"

   #######################################################
   def __handle_space(self, line, c):
      if c.isspace():
         return True

      return None

   #######################################################
   def __handle_done(self, line, c):
      if not self.done:
         return None

      fatal(self.file, line, "unexpected char '" + c + "'")

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
   def __handle_end(self, line, c):
      if not self.end:
         return None

      if c == ';':
         self.done = True
         return True

      report_expect_char(self.file, line, ";", c)

   #######################################################
   def __handle_others(self, line, c):
      if c == '{':
         self.numberOfUnclosedBraces += 1
      elif c == '}':
         self.numberOfUnclosedBraces -= 1
         if self.numberOfUnclosedBraces == 0:
            self.end = True

   #######################################################
   def __handle_char(self, line, c):
      self.__handle_space(line, c) or \
      self.__handle_done(line, c) or \
      self.__handle_begin(line, c) or \
      self.__handle_end(line, c)   or \
      self.__handle_others(line, c)

   #######################################################
   def is_done(self):
      if self.done: return self.container
      return None

   #######################################################
   def parse_line(self, line):
      self.__report_useless_annotations()
      for c in line.get_content():
         self.__handle_char(line, c)

      return self.is_done()

##########################################################

