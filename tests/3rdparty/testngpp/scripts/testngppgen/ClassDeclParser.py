#!/usr/bin/python

from Message import *
from Phase1Result import *
from Useless import Useless

##########################################################
class ClassDeclParser:
   #######################################################
   def __init__(self, content, file, line_number):
      self.content = file
      self.numberOfUnclosedBraces = 0
      self.file = file
      self.done = None
      self.numberOfUnclosedBraces = 0
      self.parse_line(Unknown(line_number, content))

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
   def __handle_done(self, line, c):
      if not self.done:
         return None

      fatal(self.file, line, "unexpected char '" + c + "' in class definition")
      
   #######################################################
   def __handle_others(self, line, c):
      if c == '{':
         self.numberOfUnclosedBraces += 1
      elif c == '}':
         if self.numberOfUnclosedBraces == 0:
            fatal(self.file, line, "found mismatched \'}'")
         self.numberOfUnclosedBraces -= 1
      elif c == ';':
         if self.numberOfUnclosedBraces == 0:
            self.done = True
      
   #######################################################
   def handle_char(self, line, c):
      self.__handle_space(line, c) or \
      self.__handle_done(line, c) or \
      self.__handle_others(line, c)

   #######################################################
   def is_done(self):
      if self.done: return Useless()
      return None

   #######################################################
   def parse_line(self, line):
      if self.done:
         fatal(self.file, line, "internal error while parsing in inner class")

      for c in line.get_content():
         self.handle_char(line, c)

      return self.is_done()

   #######################################################
   def handle_tag(self, tag):
      warning(self.file, tag, "annotation is not allowed in inner class definition")

##########################################################
