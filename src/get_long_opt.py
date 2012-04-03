#!/usr/bin/python

import getopt, sys

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

def getAssignableOptStrings(longOpts):
	return [i.toAssignable() for i in longOpts]

def getUsageString(longOpts):
	return " ".join([i.toUsage() for i in longOpts])

def usage(longOpts):
	print sys.argv[0], getUsageString(longOpts)

def getOpt(longOpts):
	try:
		return getopt.getopt(sys.argv[1:], '', getAssignableOptStrings(longOpts))
	except getopt.GetoptError, err:
		print >> sys.stderr, str(err)
		usage(longOpts)
		sys.exit(2)

def getContent(lines):
   return "\n".join(lines) + "\n"
