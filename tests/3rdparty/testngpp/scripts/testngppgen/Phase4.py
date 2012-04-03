
import os
import codecs

from Message import *

from Phase1Result import *
from TestCase import TestCase
from Fixture import Fixture
from Name import *

import Output


################################################
# record to output all fixture descs in the end file(.cxx).
fixtureDescs = []

def get_base_name(file):
    return os.path.basename(file).split('.')[0]

def get_testcase_method_name(testcase):
   if testcase.get_traditional_name():
      return testcase.get_traditional_name()

   return "test_" + str(testcase.get_line_number())

def get_testcase_display_name(testcase, group=None):
   if group == None: return testcase.get_name()
   return testcase.get_name() + escape_name("("+group+")")

def get_testcase_class_name(fixture, testcase, index=None):
   name = "TESTCASE_" + get_fixture_id(fixture) + "_" + get_testcase_method_name(testcase)
   if index == None: return name

   return name + "_" + str(index)

def get_testcase_instance_name(fixture, testcase, provider=None, index=None):
   name = "testcase_instance_" + get_fixture_id(fixture) + "_" + get_testcase_method_name(testcase)
   if provider == None: return name

   return name + "_" + provider + str(index)

def get_fixture_desc_class():
   return "TESTNGPP_NS::TestFixtureDesc"

def get_fixture_desc_var(fixture):
   return "test_fixture_desc_instance_" + get_fixture_id(fixture)

def get_file_name(testcase):
   return os.path.basename(testcase.get_file_name())

def get_depends_var(fixture, testcase):
   depends = testcase.get_depends()
   if depends == None: return "0"
   return "&" + get_testcase_instance_name(fixture, depends)

def get_fixture_id(fixture):
   return fixture.get_id()

def get_testcase_tags(testcase, fixture):
   tags = list(set(testcase.get_tags()) | set(fixture.get_tags()))
   result = ",".join(tags)
   if result == "":
      return "0"
   return result

################################################
testcase_template = '''
static struct %s
   : public TESTNGPP_NS::TestCase
{
   %s()
      : TESTNGPP_NS::TestCase
        ( "%s"
        , "%s"
        , "%s"
        , %s
        , "%s"
        , %d)
   {}

   void setFixture(TESTNGPP_NS::TestFixture* fixture)
   {
      if(fixture == 0)
      {
         belongedFixture = new %s();
      }
      else
      {
         belongedFixture = dynamic_cast<%s*>(fixture);
      }
   }

   void runTest()
   {
      %s;
   }

   TESTNGPP_NS::TestFixture* getFixture() const
   {
      return belongedFixture;
   }

   unsigned int numberOfTags() const
   {
      return %s;
   }

   const char** getTags() const
   {
      static const char* tags[] = {%s};
      return tags;
   }

private:
   %s* belongedFixture;
} %s ;

'''

testcase_invocation_template = '''
belongedFixture->%s()
'''

p_test_invocation_template='''
runParameterizedTest(belongedFixture, &%s::%s, &belongedFixture->%s, %s)
'''

################################################
class TestCaseDefGenerator:
   #############################################
   def __init__(self, file, suite, testcase, fixture):
      self.fixture = fixture
      self.testcase = testcase
      self.file = file
      self.suite = suite

   #############################################
   def __generate_p_test(self, name, index, group):
      p_test_invocation = p_test_invocation_template % ( \
           get_fixture_id(self.fixture), \
           get_testcase_method_name(self.testcase), \
           name, \
           index \
         )

      self.__generate_test_def(p_test_invocation, name, index, group)

   #############################################
   def __generate_test_def(self, test_invocation, name=None, index=None, group=None):
      testcase_def = testcase_template % ( \
         get_testcase_class_name(self.fixture, self.testcase, index), \
         get_testcase_class_name(self.fixture, self.testcase, index), \
         get_testcase_display_name(self.testcase, group), \
         self.fixture.get_name(), \
         self.suite, \
         get_depends_var(self.fixture, self.testcase), \
         get_file_name(self.testcase), \
         self.testcase.get_line_number(), \
         get_fixture_id(self.fixture), \
         get_fixture_id(self.fixture), \
         test_invocation, \
         len(self.testcase.get_tags() + self.fixture.get_tags()), \
         get_testcase_tags(self.testcase, self.fixture), \
         get_fixture_id(self.fixture), \
         get_testcase_instance_name(self.fixture, self.testcase, name, index) \
      )
      Output.output(testcase_def, self.file)

   #############################################
   def __generate_p_tests(self):
      name = self.testcase.get_data_provider_name()
      provider = self.fixture.find_data_provider(name)
      groups = provider.get_data_groups()
      for index in range(0, len(groups)):
         self.__generate_p_test(name, index, groups[index])

   #############################################
   def __generate(self):
      if self.testcase.is_p_test():
         self.__generate_p_tests()
         return

      testcase_invocation = testcase_invocation_template % ( \
           get_testcase_method_name(self.testcase) \
         )

      self.__generate_test_def(testcase_invocation)

   #############################################
   def generate(self):
      if self.testcase.has_been_generated():
         return

      depends = self.testcase.get_depends()
      if depends:
         TestCaseDefGenerator(self.file, self.suite, depends, self.fixture).generate()

      self.__generate()
      self.testcase.mark_as_generated()

################################################
def get_testcase_array_var(fixture):
   return "g_TESTCASEARRAY_" + get_fixture_id(fixture)

################################################
class TestCaseArrayGenerator:
   #############################################
   def __init__(self, file, testcase, fixture):
      self.testcase = testcase
      self.file = file
      self.fixture = fixture

   #############################################
   def __generate_p_tests(self):
      name = self.testcase.get_data_provider_name()
      provider = self.fixture.find_data_provider(name)
      groups = provider.get_data_groups()
      for index in range(0, len(groups)):
         self.__generate(name, index)

   #############################################
   def __generate(self, name=None, index=None):
      testcase_in_array = '''&%s,''' % (get_testcase_instance_name(self.fixture, self.testcase, name, index))
      Output.output(testcase_in_array, self.file)

   #############################################
   def generate(self):
      if self.testcase.is_p_test():
         self.__generate_p_tests()
         return

      self.__generate()


################################################
class TestCaseDependsVerifier:
   #############################################
   def __init__(self, testcase, fixture):
      self.testcase = testcase
      self.fixture = fixture

   #############################################
   def generate(self):
      depends = self.testcase.get_depends()
      temp = depends
      while temp != None:
        temp = temp.get_depends()
        if temp == depends:
           self.testcase.report_cyclic_depend_error()

      if not self.testcase.is_p_test():
         return

      data_provider = self.fixture.find_data_provider(self.testcase.get_data_provider_name())
      if data_provider == None:
         self.testcase.report_non_existing_data_provider()

################################################
class TestCaseSeeker:
   #############################################
   def __init__(self, fixture):
      self.fixture = fixture

   #############################################
   def generate(self):
      ScopesGenerator([self.fixture.get_scope()], None, TestCase) \
         .generate(lambda file, elem: TestCaseDependsVerifier(elem, self.fixture))


################################################
testcase_array_template_begin = '''
static TESTNGPP_NS::TestCase* %s[] = {'''

################################################
array_template_end = '''0
};


'''

################################################
class FixtureGenerator:
   #############################################
   def __init__(self, file, suite, fixture):
      self.fixture = fixture
      self.suite = suite
      self.file = file

   #############################################
   def generate_testcases(self):
      ScopesGenerator([self.fixture.get_scope()], self.file, TestCase) \
         .generate(lambda file, elem: TestCaseDefGenerator(file, self.suite, elem, self.fixture))

   #############################################
   def generate_testcase_array_content(self):
      ScopesGenerator([self.fixture.get_scope()], self.file, TestCase) \
         .generate(lambda file, elem: TestCaseArrayGenerator(file, elem, self.fixture))

   #############################################
   def generate_testcase_array(self):
      begin = testcase_array_template_begin % (get_testcase_array_var(self.fixture))

      Output.output(begin, self.file)

      self.generate_testcase_array_content()

      Output.output(array_template_end, self.file)

   #############################################
   def generate(self):
      self.generate_testcases()
      self.generate_testcase_array()

################################################
fixture_desc_template = '''
/*static*/ TESTNGPP_NS::TestFixtureDesc %s
   ( "%s"
   , "%s"
   , %s
   , (sizeof(%s)/sizeof(%s[0])) - 1
   );

'''
################################################
class FixtureDescGenerator:
   #############################################
   def __init__(self, file, fixture, recordFixture = False):
      self.fixture = fixture
      self.file = file
      self.recordFixture = recordFixture

   #############################################
   def generate(self):
      fixture_desc_def = fixture_desc_template % ( \
          get_fixture_desc_var(self.fixture), \
          self.fixture.get_name(), \
          os.path.basename(self.fixture.get_file_name()), \
          get_testcase_array_var(self.fixture), \
          get_testcase_array_var(self.fixture), \
          get_testcase_array_var(self.fixture) )

      Output.output(fixture_desc_def, self.file)

      if self.recordFixture :
          global fixtureDescs
          fixtureDescs.append(get_fixture_desc_var(self.fixture))

################################################
class FixtureDescArrayGenerator:
   #############################################
   def __init__(self, file, fixture):
      self.fixture = fixture
      self.file = file

   def generate(self):
      Output.output("&" + get_fixture_desc_var(self.fixture) + ",", self.file)

################################################
################################################
class ScopeGenerator:
   #############################################
   def __init__(self, scope, file, cls, generator_getter):
      self.scope = scope
      self.file = file
      self.cls = cls
      self.get_generator = generator_getter

   #############################################
   def generate_begin(self):
      inst = self.scope.get_inst()
      if inst != "::":
         Output.output("#" + inst, self.file)

   #############################################
   def generate_end(self):
      if self.scope.is_root_scope():
         Output.output("#endif // #" + self.scope.get_inst(), self.file)

   #############################################
   def generate_scopes(self, scopes):
      ScopesGenerator(scopes, self.file, self.cls) \
         .generate(self.get_generator)

   #############################################
   def generate_sub_scopes(self):
      self.generate_scopes(self.scope.get_sub_scopes())

   #############################################
   def generate_siblings(self):
      self.generate_scopes(self.scope.get_siblings())

   #############################################
   def generate_content(self):
      for elem in self.scope.get_elements():
         if self.cls == elem.__class__:
            self.get_generator(self.file, elem).generate()

   #############################################
   def generate(self):
      self.generate_begin()
      self.generate_content()
      self.generate_sub_scopes()
      self.generate_siblings()
      self.generate_end()

################################################
################################################
class ScopesGenerator:
   #############################################
   def __init__(self, scopes, file, cls):
     self.scopes = scopes
     self.file = file
     self.cls = cls

   #############################################
   def generate(self, generator_getter):
      for scope in self.scopes:
          ScopeGenerator(scope, self.file, self.cls, generator_getter).generate()

################################################
def get_suite_desc_name(suite):
   return "test_suite_desc_instance_" + suite

def get_fixture_array_name(suite):
   return "array_of_fixture_desc_" + suite

def get_suite_getter_name():
   return "___testngpp_test_suite_desc_getter"

##########################################################
dep_headers = [
   "internal/TestCase.h",
   "internal/TestFixtureDesc.h",
   "internal/TestSuiteDesc.h",
   "internal/DataDriven.h"
]

################################################
fixture_array_template_begin = '''
static TESTNGPP_NS::TestFixtureDesc* %s[] = {'''

################################################
suite_desc_template = '''
static TESTNGPP_NS::TestSuiteDesc %s
   ( "%s"
   , %s
   , (sizeof(%s)/sizeof(%s[0])) - 1
   );

'''

################################################
suite_getter_template = '''
extern "C" DLL_EXPORT TESTNGPP_NS::TestSuiteDesc* %s() {
   return &%s;
}

'''

################################################
class SuiteGenerator:
   #############################################
   def __init__(self, scopes, file, suite, fixture_files, recordFixture = False):
      self.scopes = scopes
      self.suite = suite
      self.file = file
      self.fixture_files = fixture_files
      self.recordFixture = recordFixture

   #############################################
   def generate_fixtures(self):
      ScopesGenerator(self.scopes, self.file, Fixture) \
         .generate(lambda file, elem: FixtureGenerator(file, self.suite, elem) )

   #############################################
   def generate_fixture_descs(self):
      ScopesGenerator(self.scopes, self.file, Fixture) \
         .generate(lambda file, elem: FixtureDescGenerator(file, elem, self.recordFixture) )

   #############################################
   def generate_fixture_desc_array(self):
      ScopesGenerator(self.scopes, self.file, Fixture) \
         .generate(lambda file, elem: FixtureDescArrayGenerator(file, elem) )

   #############################################
   def generate_fixture_array(self):
      global fixtureDescs
      if not self.recordFixture :
          for fixtureDesc in fixtureDescs :
             Output.output("extern TESTNGPP_NS::TestFixtureDesc "+fixtureDesc+";", self.file)
      fixture_array_def = fixture_array_template_begin % (get_fixture_array_name(self.suite))
      Output.output(fixture_array_def, self.file)
      self.generate_fixture_desc_array()
      if not self.recordFixture :
          # output recorded fixture descs
          for fixtureDesc in fixtureDescs :
             Output.output("&"+fixtureDesc+",", self.file)
      Output.output(array_template_end, self.file)

   #############################################
   def generate_suite_desc(self):
      suite_def = suite_desc_template % ( \
         get_suite_desc_name(self.suite), \
         self.suite, \
         get_fixture_array_name(self.suite), \
         get_fixture_array_name(self.suite), \
         get_fixture_array_name(self.suite) )

      Output.output(suite_def, self.file)


   #############################################
   def generate_suite_getter(self):
      suite_getter = suite_getter_template % ( get_suite_getter_name(), get_suite_desc_name(self.suite))
      Output.output(suite_getter, self.file)

   #############################################
   def generate_dep_headers(self):
      for header in dep_headers:
         Output.output("#include <testngpp/" + header + ">", self.file)

   #############################################
   def generate_headers(self):
      self.generate_dep_headers()

      for header in self.fixture_files:
         Output.output("#include <" + header + ">", self.file)

   #############################################
   def generate(self):
      self.generate_headers()
      self.generate_fixtures()
      self.generate_fixture_descs()
      self.generate_fixture_array()
      self.generate_suite_desc()
      if not self.recordFixture :
          self.generate_suite_getter()

################################################
def verify_testcase_deps(scopes):
   ScopesGenerator(scopes, None, Fixture) \
         .generate(lambda file, elem: TestCaseSeeker(elem) )

################################################
def phase4(fixture_files, target, scopes, encoding, recordFixture = False):
   verify_testcase_deps(scopes)

   file = None

   if Output.output == Output.output2file :
      try:
         #file = open(target, "w")
         file = codecs.open(target, mode="w", encoding=encoding)
      except IOError:
         print >> sys.stderr, "open", target, "failed"
         sys.exit(1)

   global output_encoding
   output_encoding = encoding

   SuiteGenerator(scopes, file, get_base_name(target), fixture_files, recordFixture).generate()

   if file != None :
      file.close()


################################################
