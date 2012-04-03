#!/usr/bin/python

import getopt, sys
import os

from Process import process

import Output

##########################################################
class LongOptString:
   def __init__(self, optString, example):
      self.optString = optString
      self.example = example

   def toAssignable(self):
      return self.optString + '='

   def toLongOptString(self):
      return '--' + self.optString

   def toLongAssignable(self):
      return '--' + self.optString + '='

   def toUsage(self):
      return self.toLongAssignable() + self.example

##########################################################
def getAssignableOptStrings(longOpts):
   return [i.toAssignable() for i in longOpts]

##########################################################
def getUsageString(longOpts):
   return " ".join([i.toUsage() for i in longOpts])

##########################################################
def getOpt(longOpts, argv):
   try:
      return getopt.getopt(argv, 'i:e:o:d:', getAssignableOptStrings(longOpts))
   except getopt.GetoptError, err:
      print >> sys.stderr, str(err)
      usage()
      sys.exit(2)

##########################################################
def usage():
   print "Usage:"
   print "    testngppgen", \
      getUsageString(longOpts), \
      "[-e encoding] -o target testcase1 testcase2 ..."
   print "    or"
   print "    testngppgen", \
      getUsageString(longOpts), \
      "[-e encoding] -d target_dir testcase1 testcase2 ..."

##########################################################
longOpts = []

##########################################################
def newerThan(file1, file2):
    if os.path.exists(file1) :
        file1_stat = os.stat(file1)
        file2_stat = os.stat(file2)
        if file1_stat.st_mtime >= file2_stat.st_mtime :
             return True
    return False


##########################################################
# because of adding fixture to exist file, so the last file must be always updated
# or else you may detect that when you add a new file, and it may be the new end file by chance, but the last end file not updated.
# so you'll get link error, because of the duplication of ___testngpp_test_suite_desc_getter.
def processEndFile(target_dir, cpp_file, isEnd):
    if isEnd :
        cpp_file_path = os.path.join(target_dir, cpp_file)
        if os.path.exists(cpp_file_path):
            os.remove(cpp_file_path)  # remove old .cpp file (not end file)
        cpp_file = cpp_file.replace('.cpp', '.cxx')
        cpp_file_path = os.path.join(target_dir, cpp_file)
        if os.path.exists(cpp_file_path):
            os.remove(cpp_file_path)  # new end file meets old end file, still remove old end file
    else :
        cpp_file_temp = cpp_file.replace('.cpp', '.cxx')
        cpp_file_path = os.path.join(target_dir, cpp_file_temp)
        if os.path.exists(cpp_file_path):
            os.remove(cpp_file_path)  # remove old .cxx file (end file)
        cpp_file_path = os.path.join(target_dir, cpp_file)

    return cpp_file_path

#           new.cpp   new.cxx
# old.cpp     1         23
# old.cxx     13        23

#  1 -- return cpp
#  2 -- return cxx
#  3 -- remove old

# now, there is only one testcase not processed, that is remove a test.h, the tool will not remove test.cpp


##########################################################
def generate(argv):
   optlist, fixtures = getOpt(longOpts, argv)

   target = None

   encoding = 'utf-8'

   target_dir = None

   for o, a in optlist:
      if o == "-o":
         target = a
      elif o == "-e":
         encoding = a
      elif o == "-d":
	     target_dir = a

   inputEncoding = encoding

   if target_dir != None:
      if not os.path.exists(target_dir) :
         os.makedirs(target_dir)
      while (fixtures != []) :
         fixture = fixtures.pop()
         absFixtures = []
         h_file_path=fixture
         if not os.path.isabs(fixture):
            h_file_path = os.path.join(os.getcwd(), fixture)
         absFixtures.append(h_file_path)
         h_file = os.path.basename(fixture)
         cpp_file = h_file.replace('.h', '.cpp')

         theEnd = (fixtures == [])
         if cpp_file == '':
             continue
         cpp_file_path = processEndFile(target_dir, cpp_file, theEnd)

         if newerThan(cpp_file_path, h_file_path) and (not theEnd):
            Output.output = Output.output2null   # output nothing, but record fixtureDescs.
         else :
            Output.output = Output.output2file

         process(cpp_file_path, absFixtures, inputEncoding, encoding, not theEnd)
      return

   if target == None:
      usage()
      sys.exit(1)

   absFixtures = []
   for fixture in fixtures:
      if os.path.isabs(fixture):
         absFixtures.append(fixture)
      else:
         absFixtures.append(os.path.join(os.getcwd(), fixture))

   process(target, absFixtures, inputEncoding, encoding)

