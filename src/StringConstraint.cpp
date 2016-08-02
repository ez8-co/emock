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

#include <mockcpp/types/AnyCast.h>
#include <mockcpp/StringPredict.h>
#include <mockcpp/StringConstraint.h>

MOCKCPP_NS_START

template <typename PChar>
std::string castToString(const RefAny& val)
{
   PChar p = any_cast<PChar>(val);
   if(p == 0)
   {
      return std::string((char*)"");
   }

   return std::string((char*)p);
}
////////////////////////////////////////////////////////
static std::string tryToCastParameterToString(const RefAny& val) 
{
   if(any_castable<char*>(val))
   {
      return castToString<char*>(val);
   }

   if(any_castable<unsigned char*>(val))
   {
      return castToString<unsigned char*>(val);
   }

   if(any_castable<const char*>(val))
   {
      return castToString<const char*>(val);
   }

   if(any_castable<unsigned const char*>(val))
   {
      return castToString<unsigned const char*>(val);
   }

   if(any_castable<std::string>(val))
   {
      return any_cast<std::string>(val).c_str();
   }

   return std::string("");
}

////////////////////////////////////////////////////////
StringConstraint::StringConstraint(const std::string& s, StringPredict* pred)
      : str(s), predict(pred)
{}

////////////////////////////////////////////////////////
StringConstraint::~StringConstraint()
{
   delete predict;
}

////////////////////////////////////////////////////////
bool StringConstraint::eval(const RefAny& value) const
{
	std::string s;
	s = tryToCastParameterToString(value);
	if(s.size() == 0)
	{
		return false;
	}

   if(s.size() < str.size())
   {
      return false;
   }
   
   return predict->predict(s, str);
}

////////////////////////////////////////////////////////
std::string StringConstraint::toString() const
{
   return predict->toString(str);
}

MOCKCPP_NS_END

