#ifndef __MOCKCPP_METHOD_INFO_READER_H
#define __MOCKCPP_METHOD_INFO_READER_H

#if defined(__GNUC__)
#include <mockcpp/GnuMethodInfoReader.h>
#include <mockcpp/GnuMethodIndicesChecker.h>
#endif

#if defined(_MSC_VER)
#include <mockcpp/MsvcMethodInfoReader.h>
#endif

#if !defined(__GNUC__)
#include <mockcpp/GenericMethodIndicesChecker.h>
#endif

#endif

