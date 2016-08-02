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

#include <mockcpp/types/AnyBase.h>
#include <mockcpp/types/Holder.h>

MOCKCPP_NS_START

AnyBase::AnyBase() : content(0)
{}

AnyBase::AnyBase(PlaceHolder* holder)
    : content(holder)
{
}

AnyBase::~AnyBase()
{
   delete content;
}

bool AnyBase::empty() const
{
   return !content;
}

const std::type_info& AnyBase::type() const
{
   return content ? content->type() : typeid(void);
}

std::string AnyBase::toString() const
{
   return (content==0 ? std::string("void") : content->toString());
}

std::string AnyBase::toTypeString() const
{
   return (content==0 ? std::string("void") : content->toTypeString());
}

std::string AnyBase::toTypeAndValueString() const
{
   return (content==0 ? std::string("void") : content->toTypeAndValueString());
}

AnyBase& AnyBase::swap(AnyBase& rhs)
{
   PlaceHolder* temp = content;
   content = rhs.content;
   rhs.content = temp;
   return *this;
}

PlaceHolder* AnyBase::getContent() const
{
   return content;
}

MOCKCPP_NS_END

