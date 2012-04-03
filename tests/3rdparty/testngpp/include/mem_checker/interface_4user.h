/*
 * Add by Chen Guodong <sinojelly@gmail.com>
 *
 * This file is included by user projects, can not be used in nvwa itself.
 */

/**
 * @file interface_4user.h
 *
 * Header file for checking leaks caused by unmatched new/delete or malloc/free.
 *
 * If not include this file(or any header of nvwa), you can check memory leak caused by new only, and on windows no file/line info.
 * If include this file, you can check memory leak caused by new and malloc, and it can show file/line on all platforms.
 *
 * Modify nvwa-0.8.2 to support xUnit. 
 *
 * @version 1.0, 2010/9/22
 * @author  sinojelly
 *
 */

#ifndef __INTERFACE_4USER_H__
#define __INTERFACE_4USER_H__

#ifdef __cplusplus
#include <mem_checker/interface_4cxxuser.h>
#else
#include <mem_checker/interface_4cuser.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


// when stoped mem checker, it will report nothing to xunit, but it outputs to stderr.
void stopMemChecker();
void openMemChecker();


#define STOP_MEM_CHECKER()    stopMemChecker()
#define OPEN_MEM_CHECKER()    openMemChecker()


#ifdef __cplusplus
}
#endif

#endif

