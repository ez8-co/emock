/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

