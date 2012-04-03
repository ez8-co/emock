#!/usr/bin/python

class LogicalLine:
  def __init__(self, first_phys_line, line_number):
     self.line_number = line_number
     self.content = ""
    
     self.add_line(first_phys_line)

  def add_line(self, phys_line):
     self.content += phys_line
     if len(self.content) > 0:
        if self.content[-1] == "\\":
           self.content = self.content[:-2]

  def get_line_number(self):
     return self.line_number

  def get_content(self):
     return self.content
