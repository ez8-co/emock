
#include <iostream>
#include <stdlib.h>
#include <errno.h>

#include <testngpp/runner/TestRunner.h>
#include <testngpp/utils/OptionList.h>
#include <testngpp/utils/StringList.h>
#include <testngpp/runner/ResourceCheckPoint.h>
#include <testngpp/comm/ExceptionKeywords.h>

USING_TESTNGPP_NS

////////////////////////////////////////////////////////////
void usage(const char * program)
{
   std::cerr << "usage: " 
             << program 
             << " [options] testsuites ..." 
             << std::endl
             << std::endl
             << "   -l listener      register test listener"
             << std::endl
             << "   -L path          listener searching path"
             << std::endl
             << "   -f pattern       filter patterns "
             << std::endl
             << "   -t pattern       tags filter pattern"
             << std::endl
             << "   -c number        maximum # of concurrent sandboxes"
             << std::endl
             << "   -s               using sandbox runner"
             << std::endl
             << std::endl;
   exit(1);
}

#if 0
////////////////////////////////////////////////////////////
static 
void showOptions(const OptionList& options)
{
   OptionList::Options::const_iterator i = options.options.begin();
   for(; i != options.options.end(); i++)
   {
      std::cout << "(" << i->first 
                << "," << i->second 
                << ")" << std::endl;
   }
}
#endif

////////////////////////////////////////////////////////////
static
void getSpecifiedOptions( const std::string& option
                        , StringList& results
                        , OptionList& options)
{
   OptionList::Options::const_iterator i = options.options.begin();
   for(; i != options.options.end(); i++)
   {
      if(i->first == option && i->second.size() > 0)
      {
         results.add(i->second);
      }
   }
}

////////////////////////////////////////////////////////////
static 
std::string getSingleOption(const std::string& option
                        , OptionList& options
                        , const std::string& defaultValue)
{
   OptionList::Options::const_iterator i = options.options.begin();
   for(; i != options.options.end(); i++)
   {
      if(i->first == option && i->second.size() > 0)
      {
         return i->second;
      }
   }

   return defaultValue;
}

////////////////////////////////////////////////////////////
static
bool getFlagOption(const std::string& flag, OptionList& options)
{
   OptionList::Options::const_iterator i = options.options.begin();
   for(; i != options.options.end(); i++)
   {
      if(i->first == flag)
         return true;
   }

   return false;
}
////////////////////////////////////////////////////////////
static 
unsigned int getMaxConcurrent(OptionList& options)
{
   std::string s = getSingleOption("c", options, "1");
   errno = 0;
   int result = ::strtol(s.c_str(),0,10);
   if(result < 0 || (result == 0 && errno == ERANGE))
   {
       std::cerr << "error: invalid value of option -c : " 
                 << s << std::endl;
       exit(1);
   }

   std::cout << "maximum # of sandboxes = " << result << std::endl;

   return result;
}

////////////////////////////////////////////////////////////
static
void getListeners( StringList& listeners
                 , OptionList& options)
{
   getSpecifiedOptions("l", listeners, options);
}

////////////////////////////////////////////////////////////
static
void getSearchingPathsOfListeners( StringList& paths
                                 , OptionList& options)
{
   getSpecifiedOptions("L", paths, options);
}

////////////////////////////////////////////////////////////
static
void getSpecifiedFixtures( StringList& fixtures
                         , OptionList& options)
{
   getSpecifiedOptions("f", fixtures, options);
}

////////////////////////////////////////////////////////////
static
bool useSandbox(OptionList& options)
{
   return getFlagOption("s", options);
}


////////////////////////////////////////////////////////////
int real_main(int argc, char* argv[])
{
   OptionList options;

   options.parse(argc, argv, "f:L:l:c:t:s");

   if(options.args.size() == 0)
   {
      usage("testngpp-runner");
   }

   //showOptions(options);
   
   StringList listeners;
   getListeners(listeners, options);   

   StringList searchingPathsOfListeners;
   getSearchingPathsOfListeners(searchingPathsOfListeners, options);   

   StringList fixtures;
	getSpecifiedFixtures(fixtures, options);

   bool usesSandbox = useSandbox(options);
   
   unsigned int maxConcurrent = 0;
   if(usesSandbox)
   {
      maxConcurrent = getMaxConcurrent(options);
   }
   
   std::string tagsFilterOption = getSingleOption("t", options, "*");
                                                 
   return TestRunner().runTests(useSandbox(options), maxConcurrent, options.args, listeners
                         , searchingPathsOfListeners, fixtures, tagsFilterOption);
}

int main(int argc, char* argv[])
{
   TESTNGPP_RCP rcp = TESTNGPP_SET_RESOURCE_CHECK_POINT();

   int code = 0;

   try
   {
     code = real_main(argc, argv);
     TESTNGPP_VERIFY_RESOURCE_CHECK_POINT(rcp);
   }
   catch(std::exception& error)
   {
      std::cerr << error.what() << std::endl;
   }
   catch(...)
   {
      std::cerr << "unknown exception" << std::endl;
   }
  
   return code;
}
