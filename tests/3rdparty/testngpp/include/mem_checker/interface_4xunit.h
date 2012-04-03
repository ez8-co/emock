/*
 * Add by Chen Guodong <sinojelly@gmail.com>
 *
 * This file is included in xUnit.
 */

/**
 * @file interface_4xunit.h
 *
 * xUnit use the interfaces declared in this file to support memory leak checking.
 *
 * When using this library in xUnit, it's no need to use __debug_new_counter to find the proper time to check memory leaks.
 * But it still can not be used in .c files, because of using new/delete to simulate malloc/free.
 *
 * Modify nvwa-0.8.2 to support xUnit. 
 *
 * @version 1.0, 2010/9/22
 * @author  sinojelly
 *
 */

#ifndef __INTERFACE_4XUNIT_H__
#define __INTERFACE_4XUNIT_H__

#include <mem_checker/reporter.h>


#endif

