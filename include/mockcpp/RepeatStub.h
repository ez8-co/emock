
#ifndef __MOCKCPP_REPEAT_STUB_H
#define __MOCKCPP_REPEAT_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

struct RepeatStub : public TypelessStub
{
    RepeatStub(const Any& value, unsigned int times);

    bool isCompleted() const;

    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:

    Any returnValue;
    unsigned int repeatedTimes;
    const unsigned int repeatTimes;
};

MOCKCPP_NS_END

#endif

