/*
 * Add by Chen Guodong <sinojelly@gmail.com>
 *
 */

/**
 * @file interface_4xunit.cpp
 *
 *
 * @version 1.0, 2010/9/22
 * @author  sinojelly
 *
 */
 
#include <mem_checker/interface_4xunit.h>
#include <mem_checker/reporter.h>
#include <mem_checker/check_status.h>
#include <testngpp/testngpp.h>

extern int check_leaks();


static bool report_to_xunit = true; // user can stop/open mem checker reporter to xunit

extern "C" void stopMemChecker()
{
    pauseCheckStatus(); // the following new/malloc info will not be checked in check_leaks
    report_to_xunit = false; // report nothing to xunit 
}

extern "C" void openMemChecker()
{
    reopenCheckStatus();
    report_to_xunit = true;
}


bool needToReport()
{
    return report_to_xunit;
}

extern "C" DLL_EXPORT void startMemChecker
    ( mem_checker::Reporter *infoReporter
    , mem_checker::Reporter *failureReporter)
{
    initCheckStatus();
	set_reporter(infoReporter, failureReporter);
    report_to_xunit = true;
}

extern "C" DLL_EXPORT void verifyMemChecker()
{    
	check_leaks();
    clr_reporter();
}


