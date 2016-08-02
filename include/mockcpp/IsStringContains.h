
#ifndef __MOCKCPP_IS_STRING_CONTAINS_H
#define __MOCKCPP_IS_STRING_CONTAINS_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/StringPredict.h>

MOCKCPP_NS_START

struct IsStringContains : public StringPredict
{
   bool predict(const std::string& input, const std::string& target) const;
   std::string toString(const std::string& target) const;
};

MOCKCPP_NS_END

#endif

