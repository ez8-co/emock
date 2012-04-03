
import re

from Message import *
from AnnotationParser import AnnotationParser
from TagsParser import TagsParser
from Name import *

##########################################
class TestCase:
   ########################################
   def __init__(self, name, scope, file, line, annotations):
      self.traditional_name = name[0]
      self.name             = name[1]
      self.p_test           = name[2]
      if self.name != None:
         self.name = escape_name(self.name)
      self.scope            = scope
      self.file             = file
      self.line             = line
      annotation = None
      if len(annotations) > 0:
        annotation = annotations[0]
     
      self.annotations      = AnnotationParser(annotation, {"id":None, "depends":None, "data":None, "tags":[]}).parse()
      if self.p_test and self.annotations["data"] == None:
         raw_fatal(file, line, "parameterized test should have data provider")

      self.annotations['tags'] = TagsParser(self.annotations['tags']).parse()

      self.depends          = None
      self.generated        = None

   ########################################
   def get_data_provider_name(self):
      return self.annotations['data']

   ########################################
   def is_p_test(self):
      return self.p_test

   ########################################
   def get_tags(self):
      return self.annotations['tags']
      
   ########################################
   def set_scope(self, scope):
      self.scope = scope

   ########################################
   def has_been_generated(self):
      return self.generated

   ########################################
   def mark_as_generated(self):
      self.generated = True

   ########################################
   def matches_id(self, id):
      return id != None and self.annotations["id"] == id

   ########################################
   def report_non_existing_data_provider(self):
      raw_fatal(self.file, self.line, "data provider \"" + self.get_data_provider_name() + "\" does not exist.")

   ########################################
   def report_cyclic_depend_error(self):
      raw_fatal(self.file, self.line, "cyclic depends.")


   ########################################
   def __get_depends(self):
      if self.annotations["depends"] == None:
         return None

      depends = self.scope.find_testcase_with_id(self.annotations["depends"]) 
      if depends == None:
         raw_fatal(self.file, self.line, "no testcase was specified with id=" + self.annotations["depends"])

      return depends

   ########################################
   def get_depends(self):
      if not self.depends:
         self.depends = self.__get_depends()

      return self.depends
     
   ########################################
   def show(self):
       content = "TEST(" + self.get_name() + ")"
       print content.encode('utf-8')

   ########################################
   def get_name(self):
      if not self.name:
         return self.traditional_name

      return self.name

   ########################################
   def get_traditional_name(self):
      return self.traditional_name

   ########################################
   def get_file_name(self):
      return self.file

   ########################################
   def get_line_number(self):
      return self.line

##########################################
