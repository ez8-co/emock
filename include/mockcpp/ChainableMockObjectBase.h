
#ifndef __MOCKCPP_CHAINABLE_MOCK_OBJECT_BASE_H
#define __MOCKCPP_CHAINABLE_MOCK_OBJECT_BASE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/ChainableMockMethodContainer.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockObjectBaseImpl;
struct InvocationMocker;


struct ChainableMockObjectBase 
      : public InvocationMockerNamespace
{
public:

    ~ChainableMockObjectBase();

    const std::string& getName(void) const;

    // InvocationMockerNamespace -- id("id");
    InvocationMocker* getInvocationMocker(const std::string& id) const;

    virtual void verify();

protected:

    ChainableMockMethodContainer* getMethodContainer() const;

protected:

    explicit ChainableMockObjectBase(const std::string& name);

    ChainableMockObjectBase(const ChainableMockObjectBase&);

private:

    ChainableMockObjectBase& operator=(const ChainableMockObjectBase&);

protected:

    bool shared;

private:

    ChainableMockObjectBaseImpl* This;
};

MOCKCPP_NS_END

#endif

