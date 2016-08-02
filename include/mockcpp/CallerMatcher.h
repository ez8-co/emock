
#ifndef __MOCKCPP_CALLER_MATCHER_H
#define __MOCKCPP_CALLER_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>
#include <string>

MOCKCPP_NS_START

struct Invocation;

struct CallerMatcher : public Matcher
{
	CallerMatcher(const std::string& name);

	bool matches(const Invocation& inv) const;    
    void increaseInvoked(const Invocation& inv);
    void verify() ;
    std::string toString() const ;

private:
	std::string nameOfCaller;
};

MOCKCPP_NS_END

#endif
