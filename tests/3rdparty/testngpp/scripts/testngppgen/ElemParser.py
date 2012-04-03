#!/usr/bin/python

from PreprocessScope import PreprocessScope
from PreprocessScopeParser import PreprocessScopeParser
from Useless import Useless

from Phase1Result import *

from Message import *

class ElemParser:
   #######################################################
   def __init__(self, file, parser, container):
      self.file   = file
      self.parser = parser     # for fixture
      self.elem_parser = None
      self.sub_scopes = []
      self.done = None
      self.last_line = None
      self.container = container

   #######################################################
   def __handle_tag(self, line):
      if isinstance(line, Tag):
         self.parser.handle_tag(line)
         return None

      return True

   #######################################################
   def __handle_scope(self, line):
      if isinstance(line, PreprocessScope):
         if self.parser.verify_scope(line):
            self.sub_scopes.append(line)
         return None

      return True

   #######################################################
   def __handle_sub_elem(self, line):
      elem_parser = \
           self.parser.get_elem_parser( \
              self.container, \
              self.file, \
              line);
      if elem_parser == None:
         return True

      if not self.__handle_elem_result(elem_parser.is_done()):
         self.elem_parser = ElemParser(self.file, elem_parser, elem_parser.get_container())

      return None

   #######################################################
   def __parse_normal_line(self, line):
      return self.parser.parse_line(line)

   #######################################################
   def __parse_by_myself(self, line):
      return self.__handle_tag(line) and \
             self.__handle_scope(line) and \
             self.__handle_sub_elem(line) and \
             self.__parse_normal_line(line)

   #######################################################
   def __handle_elem_result(self, elem):
      if elem:
         if not isinstance(elem, Useless):
            self.container.add_elem(elem)
         self.elem_parser = None
         return True

      return None

   #######################################################
   def __parse_elem(self, line):
      self.__handle_elem_result(self.elem_parser.parse_line(line))
      return None

   #######################################################
   def __parse_scope(self, scope):
      return PreprocessScopeParser(self.file, scope, self.parser, \
               self.__class__, self.container.get_scope()).parse()

   #######################################################
   def __handle_sub_scopes(self):
      for scope in self.sub_scopes:
         self.container.add_sub_scope(self.__parse_scope(scope))

      self.sub_scopes = []

   #######################################################
   def parse_line(self, line):
      if self.done:
         fatal(self.file, line, "testngpp generator internal error, please report bug to arthur.ii.yuan@gmail.com")

      self.last_line = line

      if self.elem_parser:
         return self.__parse_elem(line)

      self.done = self.__parse_by_myself(line)
      if self.done and self.parser.should_parse_sub_scopes():
         self.__handle_sub_scopes() 

      return self.done

   #######################################################
   def incompleted_elem_def(self):
      return self.elem_parser != None

   #######################################################
   def get_unhandled_sub_scopes(self):
      return self.sub_scopes

##########################################################
