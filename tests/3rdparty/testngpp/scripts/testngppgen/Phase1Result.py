
import sys

##########################################################
class Line:
   def __init__(self, line_number):
      self.line_number = line_number

   def get_line_number(self):
      return self.line_number

   def show(self):
      pass

##########################################################
class Tag(Line):
   def __init__(self, line_number, tag, value):
      Line.__init__(self, line_number)
      self.tag = tag
      
      self.value = value

   def get_tag(self):
      return self.tag

   def get_value(self):
      return self.value

   def show(self):
      print >> sys.stdout, self.line_number, "tag", self.tag, self.value

##########################################################
class Unknown(Line):
   def __init__(self, line_number, content):
      Line.__init__(self, line_number)
      self.content = content

   def get_content(self):
      return self.content

   def show(self):
      print >> sys.stdout, self.line_number, self.content

