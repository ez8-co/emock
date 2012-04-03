
import re

from Message import *
from Phase1Result import Tag

blank_re = re.compile( r'^\s*$', re.UNICODE)

def is_blank(str):
   return blank_re.match(str)

##########################################
class AnnotationParser:
   ########################################
   def __init__(self, tag, annotations):
      self.annotations      = annotations
      self.tags_parsed      = None

      self.tag              = tag

   ########################################
   def __setitem__(self, key, value):
      self.annotations[key] = value

   ########################################
   def __getitem__(self, key):
      return self.annotations[key]

   ########################################
   def __parse_tag(self, tag):
      if tag == None:
         return 

      if tag.get_value() == None:
         return 

      self.__parse_attrs(tag, re.split("\s*,\s*", tag.get_value()))

   ########################################
   def parse(self):
      self.__parse_tag(self.tag)
      return self.annotations

   ########################################
   def __parse_attrs(self, tag, attrs):
      for attr in attrs:
         self.__parse_attr(tag, attr)

   ########################################
   def __parse_attr(self, tag, attr):
      kv = re.split("\s*=\s*", attr)
      if len(kv) != 2:
         fatal(self.file, tag, "invalid annotation attribute definition, use key=value pair")

      matched = re.match("\s*\"(?P<value>.*)\"\s*$", kv[1])
      if matched: value = matched.group("value")
      else: value = kv[1]

      if is_blank(kv[0]) or is_blank(value):
         fatal(self.file, tag, "invalid annotation attribute definition, key or value cannot be null")

      self.__set_key_value(tag, kv[0], value)

   ########################################
   def __report_dup_key(self, tag, key):
      fatal(self.file, tag, "invalid annotation attribute definition, duplicated \"" + key + "\"")

   ########################################
   def __set_key_value(self, tag, key, value):
      try:
         if self[key] != None and len(self[key]) != 0:
            self.__report_dup_key(tag, key)

         self[key] = value
      except KeyError:
         fatal(self.file, tag, "invalid annotation attribute definition, undefined key \""+key+"\"")
     
##########################################
