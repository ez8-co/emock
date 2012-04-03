/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef __TESTNGPP_XML_BUILDER_H
#define __TESTNGPP_XML_BUILDER_H

#include <testngpp/testngpp.h>

#include <string>
#include <ostream>

TESTNGPP_NS_START

class XMLBuilder {
public:
	static XMLBuilder* create(const std::string& root);

	virtual ~XMLBuilder(){};

	virtual XMLBuilder& element(const std::string& name) = 0;
	virtual XMLBuilder& attribute(const std::string& name, const std::string& value) = 0;
	virtual XMLBuilder& text(const std::string& text) = 0;
	virtual XMLBuilder& up() const = 0;
	virtual void write(std::ostream& stream) const = 0;
};

TESTNGPP_NS_END

#endif
