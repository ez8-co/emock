
#ifndef __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H
#define __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/IsAnythingHelper.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMocker;
struct Constraint;

template <typename Builder = DummyBuilder >
struct ArgumentsMatchBuilder : public Builder
{

    Builder& with( const Any& c01 = any()
                 , const Any& c02 = any()
                 , const Any& c03 = any()
                 , const Any& c04 = any()
                 , const Any& c05 = any()
                 , const Any& c06 = any()
                 , const Any& c07 = any()
                 , const Any& c08 = any()
                 , const Any& c09 = any()
                 , const Any& c10 = any()
                 , const Any& c11 = any()
                 , const Any& c12 = any()
    );

    Builder& which(unsigned int which1, const Any& c);

    virtual ~ArgumentsMatchBuilder() {}

private:

    virtual InvocationMocker* getMocker() const = 0;

};

MOCKCPP_NS_END

#include <mockcpp/ArgumentsMatchBuilder.tcc>

#endif

