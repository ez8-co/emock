
#ifndef __MOCKPP_ANY_BASE_H
#define __MOCKPP_ANY_BASE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Holder.h>

MOCKCPP_NS_START

struct AnyBase
{
public: 

    AnyBase(void);

    AnyBase(PlaceHolder* holder);

    ~AnyBase();

public:

    bool empty() const;

    const std::type_info & type() const;

    std::string toString() const;

    std::string toTypeString() const;

    std::string toTypeAndValueString() const;

protected:

    AnyBase& swap(AnyBase& rhs);

    PlaceHolder* getContent() const;

private:

    PlaceHolder* content;

private:

    template<typename ValueType>
    friend ValueType * __type_any_cast(AnyBase *);
};

MOCKCPP_NS_END


#endif // __MOCKPP_ANY_BASE_H


