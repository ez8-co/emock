
import os



################################################
def output2file(content, file):
   if file == None:
      return

   lines = content + "\n"
   file.writelines(lines)

################################################
def output2null(content, file):
   return

################################################
output = output2file