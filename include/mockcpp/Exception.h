
#ifndef __MOCKCPP_EXCEPTION_H
#define __MOCKCPP_EXCEPTION_H

#include <mockcpp/mockcpp.h>

#include <string>

#include <exception>

MOCKCPP_NS_START

struct Exception
    : public std::exception
{
   Exception (unsigned srcline, const char* srcfile, const std::string &message);

   virtual ~Exception() throw();

   virtual std::string getMessage() const;

   unsigned getSrcLine() const;

   std::string getSrcFile() const;

   virtual const char *what() const throw();

private:

   std::string message;
   unsigned     srcline;
   std::string srcfile;
   mutable std::string  what_helper;
};

MOCKCPP_NS_END

#endif

