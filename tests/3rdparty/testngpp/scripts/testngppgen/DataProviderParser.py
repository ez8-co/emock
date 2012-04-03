#!/usr/bin/python

from Message import *
from Phase1Result import *
from DataProvider import DataProvider
import re

##########################################################
class DataProviderParser:
   #######################################################
   def __init__(self, provider, file, line_number):
      self.name = provider[0]
      self.file = file
      self.line = line_number
      self.end = None
      self.done = None
      self.numberOfUnclosedParens = 1
      self.chars = ""
      self.params = []
      self.data_provider = None
      self.number_of_groups = 0
      self.parse_line(Unknown(line_number, provider[2]))

   #######################################################
   def should_parse_sub_scopes(self):
      return False

   #######################################################
   def verify_scope(self, scope):
      return False

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
   def __parse_param(self, param):
      matched = re.match(r'\s*\(\s*(?P<param>.+)\s*\)\s*$', param)
      if not matched:
         return

      self.params.append(matched.group("param"))

   #######################################################
   def __parse_data_groups(self):
      matched = re.match(r'(?P<groups>.+)\)\s*;\s*$', self.chars)
      if not matched:
         raw_fatal(self.file, self.line, "grammar error in data provider definition 1")

      groups = matched.group("groups")
      self.number_of_groups = len(re.findall(r',\s*DATA_GROUP\s*\(', groups))

      raw_params = re.split(r'\s*,\s*DATA_GROUP\s*', groups)
      for param in raw_params:
         self.__parse_param(param)

      if len(self.params) != self.number_of_groups:
         raw_fatal(self.file, self.line, "grammar error in data provider definition 2")

   #######################################################
   def __handle_end(self, line, c):
      if not self.end:
         return None

      if c == ';':
         self.done = True
         self.__parse_data_groups()
         return True

      fatal(self.file, line, "unexpected char '" + c + "' in data provider definition")
      
   #######################################################
   def __handle_done(self, line, c):
      if not self.done:
         return None

      fatal(self.file, line, "unexpected char '" + c + "' in data provider definition")
      
   #######################################################
   def __handle_others(self, line, c):
      if c == '(':
         self.numberOfUnclosedParens += 1
      elif c == ')':
         self.numberOfUnclosedParens -= 1
         if self.numberOfUnclosedParens == 0:
            self.end = True
      
   #######################################################
   def handle_char(self, line, c):
      self.chars += c

      self.__handle_space(line, c) or \
      self.__handle_end(line, c) or \
      self.__handle_done(line, c) or \
      self.__handle_others(line, c)

   #######################################################
   def is_done(self):
      if self.done: return DataProvider(self.name, self.params)
      return None

   #######################################################
   def parse_line(self, line):
      if self.done:
         fatal(self.file, line, "internal error while parsing a data provider")

      for c in line.get_content():
         self.handle_char(line, c)

      return self.is_done()

   #######################################################
   def handle_tag(self, tag):
      warning(self.file, tag, "annotation is not allowed in data provider definition")

##########################################################
