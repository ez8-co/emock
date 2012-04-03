
#include <testngpp/internal/TestCase.h>
#include <testngpp/runner/loaders/ModuleLoader.h>

#include <mem_checker/interface_4xunit.h>


TESTNGPP_NS_START

namespace
{

struct Reporter
{
    Reporter(TestFixture *_fixture)
        : fixture(_fixture)
    {
    }

protected:
    TestFixture *fixture;
};

struct InfoReporter : public Reporter
{
    InfoReporter(TestFixture *_fixture) : Reporter(_fixture) {}
    
    void operator ()(const char *file, unsigned int line, const char *message)
    {
        fixture->reportInfo(file, line, message);
    }
};

struct FailureReporter : public Reporter
{
    FailureReporter(TestFixture *_fixture) : Reporter(_fixture) {}

    void operator ()(const char *file, unsigned int line, const char *message)
    {
        fixture->reportFailure(file, line, message, false);
    }
};

}

void TestCase::startMemChecker()
{
    typedef void (*start_t)(mem_checker::Reporter *, mem_checker::Reporter *);
    start_t starter = (start_t)loader->findSymbol("startMemChecker");

    if (fixtureCloneAsReporter == 0)
    {
        fixtureCloneAsReporter = getFixture()->clone();
    }
    starter( mem_checker::createReporter(InfoReporter(fixtureCloneAsReporter))
           , mem_checker::createReporter(FailureReporter(fixtureCloneAsReporter))); // TODO: Reporter is new in runner.exe, and used in .dll. is this ok?
}

//void TestCase::verifyMemChecker()
//{
//    typedef void (*verify_t)(void);
//    verify_t verifier = (verify_t)loader->findSymbol("verifyMemChecker");
//    verifier(); 
//}


TESTNGPP_NS_END






