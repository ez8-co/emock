/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#include <mockcpp/ConstraintSet.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/Invocation.h>

#include <vector>

MOCKCPP_NS_START

struct ConstraintSetImpl
{
    typedef std::vector<Constraint*> Vector;

    Vector constraints;

    ~ConstraintSetImpl();

    bool matches(const Invocation& inv) const;

    unsigned int numberOfValidConstraint(void) const;

    std::string toString() const;
};

////////////////////////////////////////////////////////////
std::string
ConstraintSetImpl::toString() const
{
    oss_t oss;

    unsigned int n = numberOfValidConstraint();
    for (unsigned int i = 0; i < n; i++)
    {
      oss << constraints[i]->toString();
      if (i < n-1) oss << ", ";
	 }

    return oss.str();
}

////////////////////////////////////////////////////////////
unsigned int
ConstraintSetImpl::numberOfValidConstraint() const
{
    for (int i = (int)constraints.size()-1; i >= 0; i--)
    {
      if(!isAnyConstraint(constraints[i]))
        return i + 1;
    }
	
    return 0;
}
////////////////////////////////////////////////////////////
ConstraintSetImpl::~ConstraintSetImpl()
{
    for (int i=0; i<(int)constraints.size(); i++)
    {
      delete constraints[i];
    }

    constraints.clear();

	return;
}

////////////////////////////////////////////////////////////
bool
ConstraintSetImpl::matches(const Invocation& inv) const
{
    for (int i=0; i<(int)constraints.size(); i++)
    {
      if (!constraints[i]->eval(inv.getParameter(i+1)))
      {
        return false;
      }
    }

    return true;
}

////////////////////////////////////////////////////////////
#define INIT_CONSTRAINT(i) This->constraints.push_back(p##i)

ConstraintSet::ConstraintSet(unsigned int which, Constraint* p)
   : This(new ConstraintSetImpl())
{
    if(which >= 12 || p == 0) return;

    for(unsigned int i=0; i<which; i++)
    {
        This->constraints.push_back(any());
    }

    
    This->constraints.push_back(p);
}

ConstraintSet::ConstraintSet(
               Constraint* p1
             , Constraint* p2
             , Constraint* p3
             , Constraint* p4
             , Constraint* p5
             , Constraint* p6
             , Constraint* p7
             , Constraint* p8
             , Constraint* p9
             , Constraint* p10
             , Constraint* p11
             , Constraint* p12
   )
   : This(new ConstraintSetImpl())
{
    INIT_CONSTRAINT(1);
    INIT_CONSTRAINT(2);
    INIT_CONSTRAINT(3);
    INIT_CONSTRAINT(4);
    INIT_CONSTRAINT(5);
    INIT_CONSTRAINT(6);
    INIT_CONSTRAINT(7);
    INIT_CONSTRAINT(8);
    INIT_CONSTRAINT(9);
    INIT_CONSTRAINT(10);
    INIT_CONSTRAINT(11);
    INIT_CONSTRAINT(12);
}

////////////////////////////////////////////////////////////
ConstraintSet::~ConstraintSet()
{
    delete This;
}

////////////////////////////////////////////////////////////
bool ConstraintSet::matches(const Invocation& inv) const
{
    return This->matches(inv);    
}

////////////////////////////////////////////////////////////
std::string ConstraintSet::toString() const
{
    oss_t oss;

    oss << ".with(" << This->toString() << ")";

    return oss.str();
}

////////////////////////////////////////////////////////////
void ConstraintSet::verify(void) 
{
}

////////////////////////////////////////////////////////////

MOCKCPP_NS_END

