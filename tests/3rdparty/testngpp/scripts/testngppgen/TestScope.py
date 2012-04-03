
import sys

from TestCase import TestCase
from DataProvider import DataProvider

############################################
class TestScope:
   #########################################
   def __init__(self, inst, expr, parent):
      self.inst = inst
      self.expr = expr
      self.elements = []
      self.sub_scopes = []
      self.siblings = []
      self.parent = parent

   #########################################
   def find_data_provider(self, name):
      for elem in self.elements:
         if isinstance(elem, DataProvider) and elem.get_name() == name:
            return elem

      return None

   #########################################
   def find_testcase_with_id(self, id):
      for elem in self.elements:
        if isinstance(elem, TestCase) and elem.matches_id(id):
            return elem

      if self.parent:
         return self.parent.find_testcase_with_id(id)

      return None

   #########################################
   def show(self):
      print "#" + self.inst, self.expr

      for elem in self.elements:
         elem.show()

      for scope in self.sub_scopes:
         scope.show()

      for scope in self.siblings:
         scope.show()

   #########################################
   def equals(self, scope):
      if self.inst != scope.inst or self.expr != scope.expr:
         return None

      if len(self.siblings) != len(scope.siblings):
         return None

      for i in range(len(self.siblings)):
         if not self.siblings[i].equals(scope.siblings[i]):
            return None

      return True

   def get_scope(self):
      return self

   #########################################
   def add_sub_scopes(self, scopes):
      for s in scopes:
        self.add_sub_scope(s)
      
   #########################################
   def merge(self, scope):
      if self.equals(scope):
         for elem in scope.get_elements():
            self.add_elem(elem)
         for i in range(len(self.siblings)):
            self.siblings[i].merge(scope.siblings[i])
         self.add_sub_scopes(scope.get_sub_scopes())

         return True

      return None

   #########################################
   def get_inst(self):
      result = self.inst
      if self.expr:
         result = result + " " + self.expr

      return result

   #########################################
   def get_elements(self):
      return self.elements

   #########################################
   def get_sub_scopes(self):
      return self.sub_scopes
   
   #########################################
   def get_siblings(self):
      return self.siblings

   #########################################
   def is_root_scope(self):
      return self.inst == "ifdef" or \
             self.inst == "ifndef" or \
             self.inst == "if"

   #########################################
   def add_elem(self, elem):
      elem.set_scope(self)
      self.elements.append(elem)

   #########################################
   def add_sub_scope(self, scope):
      for s in self.sub_scopes:
         if s.merge(scope):
            return 

      scope.parent = self
      self.sub_scopes.append(scope)

   #########################################
   def add_sibling(self, scope):
      self.siblings.append(scope)

############################################
