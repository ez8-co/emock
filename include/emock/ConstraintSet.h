/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
   
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

#ifndef __EMOCK_CONSTRAINT_SET_H
#define __EMOCK_CONSTRAINT_SET_H

#include <emock/emock.h>
#include <emock/StatelessMatcher.h>
#include <emock/IsAnythingHelper.h>

EMOCK_NS_START

struct Invocation;
struct Constraint;
struct ConstraintSetImpl;

struct ConstraintSet: public StatelessMatcher
{
    ConstraintSet(unsigned int which, Constraint* p);

    ConstraintSet( Constraint* p01 = any()
                 , Constraint* p02 = any()
                 , Constraint* p03 = any()
                 , Constraint* p04 = any()
                 , Constraint* p05 = any()
                 , Constraint* p06 = any()
                 , Constraint* p07 = any()
                 , Constraint* p08 = any()
                 , Constraint* p09 = any()
                 , Constraint* p10 = any()
                 , Constraint* p11 = any()
                 , Constraint* p12 = any()
    );

    ~ConstraintSet();

    virtual bool matches(const Invocation& inv) const;

    virtual std::string toString() const;

    virtual void verify(void);

private:

    ConstraintSetImpl* This;
};

EMOCK_NS_END

#endif

