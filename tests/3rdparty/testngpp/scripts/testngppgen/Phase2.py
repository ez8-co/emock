#!/usr/bin/python

import sys
import re
import os
import codecs

from Phase1Result import *

from PreprocessScope import *

from Message import *

cpp_re  = re.compile( r'^\s*#\s*(?P<instruction>\w+)(\s+(?P<rest>.*))?$', re.UNICODE)
macro_re = re.compile( r'^\s*[A-Za-z_][A-Za-z0-9_]*\s*$', re.UNICODE)

##########################################################
def create_cont(lines):
   return {'type':'CONT', 'lines':lines}

##########################################################
def create_done(lines, root):
   return {'type':'DONE', 'lines':lines, 'root':root}

##########################################################
def is_scope_inst(inst):
   return inst == "if" or \
          inst == "ifdef" or \
          inst == "ifndef" or \
          inst == "else" or \
          inst == "elif" or \
          inst == "endif"

##########################################################
class BaseScope(PreprocessScope):
   #######################################################
   def __init__(self, file, line, parent, name, expr):
      PreprocessScope.__init__(self, file, line, parent, name, expr)

   def stay_in_zero(self):
      return self.is_zero() or (self.parent and self.parent.stay_in_zero())

   #######################################################
   def is_zero(self):
      return None

   #######################################################
   def is_one(self):
      return None

   #######################################################
   def add_line(self, lines):
      line = lines[0]
      if not self.stay_in_zero():
         self.lines.append(lines[0])

      return create_cont(lines[1:])

   #######################################################
   def handle_done(self, result):
      if result['root'] == self:
         if self.parent != None:
            self.parent.merge(self)

         return create_cont(result['lines'])

      return result

   #######################################################
   def parse(self, lines):
       lns = lines

       while len(lns) > 0:
          result = self.parse_line(lns)
          if result['type'] == 'DONE':
             return self.handle_done(result)
          else:
             lns = result['lines']

       return create_done([], self)

   #######################################################
   def parse_line(self, lines):
      line = lines[0]

      if isinstance(line, Tag):
         return self.add_line(lines)

      matched = cpp_re.match(line.get_content())
      if not matched:
         return self.add_line(lines)

      return self.parse_cpp_line(lines, matched.group('instruction'), matched.group('rest')) 

   #######################################################
   def parse_cpp_line(self, lines, inst, rest):
      if not is_scope_inst(inst):
         return self.add_line(lines)

      expr = rest
      if rest != None:
         expr = "".join(re.split("\s*",rest))

      return self.parse_scope_inst(lines, inst, expr)

   #######################################################
   def add_scope(self, scope):
      if not self.stay_in_zero():
         self.lines.append(scope)

   #######################################################
   def start_scope(self, scope, lines):
      return scope.parse(lines[1:])

   #######################################################
   def start_ifdef_scope(self, lines, rest, isIfndef):
      matched = macro_re.match(rest)
      if not matched:
         fatal(self.file, lines[0], "grammar error: only macro allowed")

      return self.start_scope(IfdefScope(self.file, lines[0], self, rest, isIfndef), lines)

   #######################################################
   def parse_scope_inst(self, lines, inst, rest):
      if inst == "if":
         return self.start_scope(IfScope(self.file, lines[0], self, rest, None), lines)
      elif inst == "ifndef":
         return self.start_ifdef_scope(lines, rest, True)
      elif inst == "ifdef":
         return self.start_ifdef_scope(lines, rest, None)

      return self.parse_other_insts(lines, inst, rest)

   #######################################################
   def parse_other_insts(self, lines, inst, rest):
      fatal(self.file, lines[0], "should not be here")

##########################################################
class GlobalScope(BaseScope):
   #######################################################
   def __init__(self, file):
       BaseScope.__init__(self, file, 1, None, "::", None)

   #######################################################
   def parse_other_insts(self, lines, inst, rest):
       fatal(self.file, lines[0], "(global) unexpected preprocessor instruction \"" + inst + "\"")

##########################################################
class ConditionScope(BaseScope):
   #######################################################
   def __init__(self, file, line, parent, root, name, expr):
       BaseScope.__init__(self, file, line.get_line_number(), parent, name, expr)
       self.root = root
       if root == None:
          self.root = self

   #######################################################
   def add_elses(self, scope, lines):
      #if not self.root.stay_in_zero():
      self.root.elses.append(scope)

      return scope.parse(lines[1:])

   #######################################################
   def parse_other_insts(self, lines, inst, rest):
      '''#else, #elif, #endif'''
      if inst == 'endif':
         return create_done(lines[1:], self.root)

      return self.parse_else_scope(lines, inst, rest)

   #######################################################
   def parse_else_scope(self, lines, inst, rest):
      fatal(self.file, lines[0], "should not be here")

   #######################################################
   def is_digit(self):
      return self.is_zero() or self.is_one()

##########################################################
hex_re = re.compile( r'^\s*(?P<value>0[xX][A-Fa-f0-9]+)\s*$' )
oct_re = re.compile( r'^\s*(?P<value>0[0-7]*)\s*$' )
dec_re = re.compile( r'^\s*(?P<value>[1-9][0-9]*)\s*$' )

def convert_to_int(file, line, str, base):
   try:
      return int(str, base)
   except ValueError:
      fatal(file, line, "Invalid int literal " + str)
     
##########################################################
def is_number(file, line, content):
   matched = dec_re.match(content)
   if matched:
      return convert_to_int(file, line, matched.group("value"), 10)

   matched = hex_re.match(content)
   if matched:
      return convert_to_int(file, line, matched.group("value"), 16)

   matched = oct_re.match(content)
   if matched:
      return convert_to_int(file, line, matched.group("value"), 8)

   return None

##########################################################
def getIfName(isElif):
   if isElif:
      return "elif"
   return "if"

##########################################################
class IfScope(ConditionScope):   
   #######################################################
   def __init__(self, file, line, parent, rest, root):
      if root and (root.is_zero() or root.is_one()):
         fatal(self.file, line, "#if 0 or #if 1 does not allow #elif")

      self.rest = rest

      isElif = True

      if root == None:
         isElif = None

      self.zero = None
      self.one = None

      value = is_number(file, line, rest)
      if value == 0:   self.zero = True
      elif value > 0:  self.one = True

      ConditionScope.__init__(self, file, line, parent, root, getIfName(isElif), rest)

   #######################################################
   def is_zero(self):
      return self.zero

   #######################################################
   def is_one(self):
      return self.one

   def get_scope_cls(self, inst):
      if inst == "elif":
         return IfScope

      return ElseScope

   #######################################################
   def get_scope(self, line, inst, rest):
      return self.get_scope_cls(inst)(self.file, line, self.parent, rest, self.root)

   #######################################################
   def parse_else_scope(self, lines, inst, rest):
      return self.add_elses(self.get_scope(lines[0], inst, rest), lines)

##########################################################
def getIfdefName(isIfndef):
   if isIfndef:
      return "ifndef"

   return "ifdef"

##########################################################
class IfdefScope(ConditionScope):
   #######################################################
   def __init__(self, file, line, parent, rest, isIfndef):
      ConditionScope.__init__(self, file, line, parent, None, getIfdefName(isIfndef), rest)
      self.isIfndef = isIfndef

   #######################################################
   def parse_else_scope(self, lines, inst, rest):
      if inst == "elif":
         fatal(self.file, lines[0], "unexpected preprocessor instruction " + inst)

      return self.add_elses(ElseScope(self.file, lines[0], self.parent, rest, self), lines)

##########################################################
class ElseScope(ConditionScope):
   #######################################################
   def __init__(self, file, line, parent, rest, root):
      ConditionScope.__init__(self, file, line, parent, root, "else", None)
   
   #######################################################
   def parse_else_scope(self, lines, inst, rest):
      fatal(self.file, lines[0], "unexpected preprocessor instruction " + inst)

   #######################################################
   def is_zero(self):
      return self.root.is_one()

   #######################################################
   def is_one(self):
      return self.root.is_zero()

##########################################################
def phase2(lines, file):
   scope = GlobalScope(file)
   scope.parse(lines)
   return scope


