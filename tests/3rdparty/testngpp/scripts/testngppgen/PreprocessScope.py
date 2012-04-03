#!/usr/bin/python

#####################################
class PreprocessScope:
   ##################################
   def __init__(self, file, line, parent, inst, expr):
      # Parent Scope
      self.parent = parent 

      # Instrution
      self.inst   = inst   

      # Expression
      self.expr   = expr   

      # Lines in current scope (Tag, Scope, Unknown)
      self.lines  = []     

      # sibling scopes (only #if, #ifndef, #ifdef has this fields)
      # ( contains #elif #else scope )
      self.elses  = []     

      # file name
      self.file   = file
      self.line   = line

   ##################################
   def show(self):
      print "#" + self.inst, self.expr

      for line in self.lines:
         line.show()

      for scope in self.elses:
         scope.show()

   ##################################
   def merge(self, scope):
      if scope.is_one():
        self.lines += scope.lines
      elif scope.is_zero():
        assert len(scope.elses) <= 1
        if len(scope.elses) > 0:
           self.lines += scope.elses[0].lines
      else:
        self.add_scope(scope)


   ##################################
   def get_file_name(self):
      return self.file

   ##################################
   def get_line_number(self):
      return self.line

   ##################################
   def get_parent(self):
      return self.parent

   ##################################
   def get_inst(self):
      return self.inst

   ##################################
   def get_lines(self):
      return self.lines

   ##################################
   def get_elses(self):
      return self.elses

   ##################################
   def get_expr(self):
      return self.expr

#####################################
