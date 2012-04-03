#!/usr/bin/python

import sys
import os.path
from get_long_opt import *

delegatedMethodDefFileName = "DelegatedMethodDef.h"
argumentListDefFileName = "ArgumentsListDef.h"
methodTypeTraitsDefFileName = "MethodTypeTraitsDef.h"
maxParametersOpt   = LongOptString("max-parameters", "12")
includePathOpt      = LongOptString("include-path", "/home/darwin/mockcpp/include")

longOpts = [ maxParametersOpt
           , includePathOpt]

def getArgumentListDefContent(maxParameters):
   lineStr = ''', typename P%d = UselessType'''
   lines = []
   for i in range(0, maxParameters+1):
      lines.append(lineStr % i)

   return getContent(lines)

def generateArgumentListDef(includePath, maxParameters):
   content = getArgumentListDefContent(maxParameters)
   writeFile(includePath + "/" + argumentListDefFileName, content)

def getMethodTypeTraitsDefContent(maxParameters):
   lineStr0 = '''MOCKCPP_METHOD_TYPE_TRAITS_DEF(%d);'''
   lineStr1 = '''MOCKCPP_CONST_METHOD_TYPE_TRAITS_DEF(%d);'''
   lines = []
   for i in range(0, maxParameters+1):
      lines.append(lineStr0 % i)
      lines.append(lineStr1 % i)

   return getContent(lines)

def generateMethodTypeTraitsDef(includePath, maxParameters):
   content = getMethodTypeTraitsDefContent(maxParameters)
   writeFile(includePath + "/" + methodTypeTraitsDefFileName, content)

def getDelegatedMethodDefContent(maxParameters):
   lineStr0 = '''MOCKCPP_DELEGATED_METHOD_DEF(%d);'''
   lineStr1 = '''MOCKCPP_CONST_DELEGATED_METHOD_DEF(%d);'''
   lines = []
   for i in range(0, maxParameters+1):
      lines.append(lineStr0 % i)
      lines.append(lineStr1 % i)

   return getContent(lines)

def generateDelegatedMethodDef(includePath, maxParameters):
   content = getDelegatedMethodDefContent(maxParameters)
   writeFile(includePath + "/" + delegatedMethodDefFileName, content)

def writeFile(name, content):
   FILE = open(name, "w")
   FILE.writelines(content)
   FILE.close()

def main():
   optlist, args = getOpt(longOpts)

   maxParameters = 12
   includePath = "."

   for o, a in optlist:
      if o == maxParametersOpt.toLongOptString():
         maxParameters = int(a)
      if o == includePathOpt.toLongOptString():
         includePath = a

   if delegatedMethodDefFileName in args:
      generateDelegatedMethodDef(includePath, maxParameters)

   if argumentListDefFileName in args:
      generateArgumentListDef(includePath, maxParameters)

   if methodTypeTraitsDefFileName in args:
      generateMethodTypeTraitsDef(includePath, maxParameters)


if __name__ == "__main__":
    main()
