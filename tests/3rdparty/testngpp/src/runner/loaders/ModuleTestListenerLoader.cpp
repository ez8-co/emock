

#include <string>
#include <sstream>
#include <iostream>

#include <testngpp/comm/ExceptionKeywords.h>
#include <testngpp/utils/StringToOptions.h>

#include <testngpp/internal/Error.h>

#include <testngpp/listener/TestListener.h>

#include <testngpp/runner/loaders/ModuleLoader.h>
#include <testngpp/runner/loaders/ModuleTestListenerLoader.h>


TESTNGPP_NS_START

struct ModuleTestListenerLoaderImpl
{
   ModuleTestListenerLoaderImpl( ModuleLoader* moduleLoader);

	~ModuleTestListenerLoaderImpl();

   void destroyArgs();
   void destroyListener();

	void load( const StringList& searchingPaths
            , TestResultReporter* resultReporter
				, TestSuiteResultReporter* suiteResultReporter
				, TestCaseResultReporter* caseResultReporter);

   void parseCommandLine(const std::string& cl);

   std::string name;
   StringToOptions::CArgs args; 
   
   TestListener* listener;
   ModuleLoader* loader;
};

namespace
{
   std::string getDestroySymbolName(const std::string& name)
   {
      std::stringstream ss;
      ss << name << "_destroy_instance";
      return ss.str();
   }
}

///////////////////////////////////////////////////////////////
ModuleTestListenerLoaderImpl::
ModuleTestListenerLoaderImpl(ModuleLoader* moduleLoader)
   : loader(moduleLoader)
   , listener(0)
{
}

///////////////////////////////////////////////////////////////
void
ModuleTestListenerLoaderImpl::
parseCommandLine(const std::string& cl)
{
   args = StringToOptions::parse(cl);

   if(args.first == 0)
   {
      name = "";
      return;
   }

   name = args.second[0];
}

///////////////////////////////////////////////////////////////
void
ModuleTestListenerLoaderImpl::destroyListener()
{
   typedef void (*TestListenerDestroy)(TestListener*);
   TestListenerDestroy destroy = 0;

   __TESTNGPP_TRY
   {
      destroy =  (TestListenerDestroy) \
         loader->findSymbol(getDestroySymbolName(name));

      destroy(listener);
   }
   __TESTNGPP_CATCH_ALL
   {
      delete listener;
   }
   __TESTNGPP_FINALLY
   {
      listener = 0;
      loader->unload();
   }
   __TESTNGPP_DONE

}

///////////////////////////////////////////////////////////////
void
ModuleTestListenerLoaderImpl::destroyArgs()
{
   for(int i = 0; i < args.first; i++)
   {
      delete [] args.second[i];
   }

   delete [] args.second;
}

///////////////////////////////////////////////////////////////
ModuleTestListenerLoaderImpl::
~ModuleTestListenerLoaderImpl()
{
   destroyArgs();

   if(listener != 0)
   {
      destroyListener();
   }

   if(loader != 0)
   {
      loader->unload();
      delete loader;
   }
}

///////////////////////////////////////////////////////////////
ModuleTestListenerLoader::
ModuleTestListenerLoader(ModuleLoader* loader)
   : This(new ModuleTestListenerLoaderImpl(loader))
{
}

///////////////////////////////////////////////////////////////
ModuleTestListenerLoader::
~ModuleTestListenerLoader()
{
   delete This;
}

namespace
{
   std::string getListenerSharedObjectName(const std::string& name)
   {
      std::stringstream ss;
	   ss <<
#if !defined(_MSC_VER)
      "lib" << 
#endif
      name;

      return ss.str();
   }

   std::string getCreaterSymbolName(const std::string& name)
   {
      std::stringstream ss;
      std::string module = name;

      size_t pos = module.find(".dll");
      if (pos != std::string::npos)
      {
          module = module.substr(0, pos);
      }
      
      ss << module << "_create_instance";
      return ss.str();
   }
}

///////////////////////////////////////////////////////////////
void
ModuleTestListenerLoaderImpl::
load( const StringList& searchingPaths
    , TestResultReporter* resultReporter
    , TestSuiteResultReporter* suiteResultReporter
    , TestCaseResultReporter* caseResultReporter)
{
   loader->load(searchingPaths, getListenerSharedObjectName(name));

   typedef TestListener* (*TestListenerCreater) \
                  ( TestResultReporter* \
						, TestSuiteResultReporter* \
						, TestCaseResultReporter* \
						, int, char**);

   TestListenerCreater create = (TestListenerCreater) \
       loader->findSymbol(getCreaterSymbolName(name));

   listener = create( resultReporter 
                    , suiteResultReporter
                    , caseResultReporter
                    , args.first
                    , args.second);
   if(listener == 0)
   {
      throw Error("Cannot create listener");
   }
}

/////////////////////////////////////////////////////////////////
TestListener*
ModuleTestListenerLoader::
load( const StringList& searchingPaths
    , const std::string& cl
    , TestResultReporter* resultReporter
    , TestSuiteResultReporter* suiteResultReporter
    , TestCaseResultReporter* caseResultReporter)
{
   This->parseCommandLine(cl);

   std::cout << "loading " << This->name << " ... "; std::cout.flush();

   __TESTNGPP_TRY
   {
      This->load(searchingPaths, resultReporter, suiteResultReporter, caseResultReporter);
      std::cout << "OK" << std::endl;
   }
   __TESTNGPP_CATCH(Error& e)
   {
      std::cerr << e.what() << std::endl;
   }
   __TESTNGPP_END_TRY

   return This->listener;
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

