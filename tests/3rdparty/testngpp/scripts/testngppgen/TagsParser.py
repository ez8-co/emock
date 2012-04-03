
import re

from Message import *
from AnnotationParser import AnnotationParser

tags_re1 = re.compile( r'^\"(?P<tags>[A-Za-z0-9_\s]*)\"$', re.UNICODE)
tags_re2 = re.compile( r'^(?P<tags>[A-Za-z0-9_\s]*)$', re.UNICODE)

##########################################
class TagsParser:
   ########################################
   def __init__(self, tags):
      self.tags_parsed      = None
      self.tags             = tags

   ########################################
   def __parse_tags(self, tags):
      matched = tags_re1.match(tags)
      if not matched:
         matched = tags_re2.match(tags)

      if not matched:
         fatal(self.file, self.line, "invalid annoation attribute value of \"tags\"")

      return ["\""+tag+"\""  for tag in re.split(r'\s+', matched.group("tags"))]

   def parse(self):
      if self.tags == [] or self.tags == None:
         return []

      return self.__parse_tags(self.tags)

##########################################
