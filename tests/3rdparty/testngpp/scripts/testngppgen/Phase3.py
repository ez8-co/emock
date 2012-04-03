#!/usr/bin/python

import re
import codecs

from Phase1Result import *
from PreprocessScopeParser import *
from ElemParser import ElemParser

from FixtureParser import FixtureParser

from Message import *

fixture_re1  = re.compile( \
   r'''^\s*FIXTURE\s*\(\s*(?P<fixtureId>[A-Za-z_][A-Za-z0-9_]*)\s*(,\s*(?P<fixtureName>.+))?\s*\)\s*''', \
   re.UNICODE)

fixture_re2  = re.compile( \
   r'''^\s*(struct|class)\s+(?P<fixtureId>[A-Za-z_][A-Za-z0-9_]*)\s*:\s*public\s+((TESTNGPP_NS|TESTCPP_NS|testngpp|testcpp)\s*::)?\s*TestFixture\s*$''' )

fixture_re3  = re.compile( \
   r'''^\s*(struct|class)\s+(?P<fixtureId>[A-Za-z_][A-Za-z0-9_]*)\s*:\s*public\s+((CxxTest)\s*::)?\s*TestSuite\s*$''' )
##########################################################
def is_fixture_def(line):
   matched = fixture_re1.match(line)
   if matched:
      return "Test", matched.group("fixtureId"), matched.group("fixtureName")

   matched = fixture_re2.match(line)
   if matched:
      return "", matched.group("fixtureId"), None

   matched = fixture_re3.match(line)
   if matched:
      return "", matched.group("fixtureId"), None

   return None
   
##########################################################
class GlobalParser:
   def __init__(self, file):
      self.file = file
      self.annotations = []

   #######################################################
   def should_parse_sub_scopes(self):
      return True

   #######################################################
   def get_elem_parser(self, container, file, line):
      name = is_fixture_def(line.get_content())
      if name == None:
        return None

      return self.__create_fixture_parser(name, container.get_scope(), file, line.get_line_number())

   #######################################################
   def __check_dup_annotation(self, new_anno):
      for anno in self.annotations:
         if anno.get_tag() == new_anno.get_tag():
            fatal(self.file, new_anno, "duplicated annotation is not allowed, @" + new_anno.get_tag())
         
   #######################################################
   def __is_fixture_annotation(self, anno):
      self.__check_dup_annotation(anno)
      return anno.get_tag() in ["fixture"]

   #######################################################
   def handle_tag(self, anno):
      if self.__is_fixture_annotation(anno):
         self.annotations.append(anno)
      else:
         warning(self.file, anno, "unknown annotation @" + anno.get_tag())

   #######################################################
   def __report_useless_annotations(self):
      if len(self.annotations) > 0:
         for anno in self.annotations:
            warning(self.file, anno, "useless annotation @" + anno.get_tag())

      self.annotations = []

   #######################################################
   def verify_scope(self, tag):
      return True

   #######################################################
   def __create_fixture_parser(self, elem_name, scope, file, line):
      annos = self.annotations
      self.annotations = []
      return FixtureParser(elem_name, file, line, annos)

   #######################################################
   def get_type_name(self):
      return "fixture"

   #######################################################
   def parse_line(self, line):
      self.__report_useless_annotations()
      return None

   #######################################################
   def get_container(self):
      return None

##########################################################
def phase3(globalScope, file):
   return PreprocessScopeParser(file, globalScope, GlobalParser(file), ElemParser, None).parse()

