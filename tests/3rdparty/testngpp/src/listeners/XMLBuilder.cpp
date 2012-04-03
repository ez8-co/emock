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

#include "XMLBuilder.h"

#include <testngpp/testngpp.h>

#include <ostream>
#include <sstream>
#include <vector>
#include <map>

TESTNGPP_NS_START

///////////////////////////////////////////////////////////
struct Attribute
{
	Attribute(const std::string& name, const std::string& value);

	std::string name;
	std::string value;
};

///////////////////////////////////////////////////////////
Attribute::Attribute(const std::string& name, const std::string& value)
	: name(name), value(value)
{
}

///////////////////////////////////////////////////////////
class SimpleXMLBuilder : public XMLBuilder
{
public:
	SimpleXMLBuilder(const std::string& name);
	SimpleXMLBuilder(const std::string& name, SimpleXMLBuilder* parent);
	virtual ~SimpleXMLBuilder();

	XMLBuilder& element(const std::string& name);
	XMLBuilder& attribute(const std::string& name, const std::string& value);
	XMLBuilder& text(const std::string& text);
	XMLBuilder& up() const;
	void write(std::ostream& os) const;

private:
	void writeElement(std::ostream& os, int level) const;
	void writeAttributes(std::ostream& os) const;
	void writeChildElements(std::ostream& os, int level) const;
	void writeIndentation(std::ostream& os, int level) const;
	std::string escape(const std::string& str) const;

	std::string name;
	std::string* txt;
	SimpleXMLBuilder* parent;
	std::vector<SimpleXMLBuilder*> children;
	std::vector<Attribute*> attributes;
};

///////////////////////////////////////////////////////////
XMLBuilder* XMLBuilder::create(const std::string& root)
{
	return new SimpleXMLBuilder(root);
}

///////////////////////////////////////////////////////////
SimpleXMLBuilder::SimpleXMLBuilder(const std::string& name)
	: name(name), parent(NULL), txt(NULL)
{
}

///////////////////////////////////////////////////////////
SimpleXMLBuilder::SimpleXMLBuilder(const std::string& name,
		SimpleXMLBuilder* parent)
	: name(name), parent(parent), txt(NULL)
{
	parent->children.push_back(this);
}

///////////////////////////////////////////////////////////
SimpleXMLBuilder::~SimpleXMLBuilder()
{
	std::vector<SimpleXMLBuilder*>::iterator elemIt;
	for (elemIt = children.begin(); elemIt < children.end(); elemIt++)
		delete *elemIt;

	std::vector<Attribute*>::iterator attrIt;
	for (attrIt = attributes.begin(); attrIt < attributes.end(); attrIt++)
		delete *attrIt;

	if (txt != NULL)
		delete txt;
}

///////////////////////////////////////////////////////////
void SimpleXMLBuilder::write(std::ostream& os) const
{
	if (parent != NULL)
	{
		parent->write(os);
		return;
	}

	os << "<?xml version=\"1.0\"?>" << std::endl;
	writeElement(os, 0);
}

///////////////////////////////////////////////////////////
void SimpleXMLBuilder::writeElement(std::ostream& os,
		int level) const
{
	writeIndentation(os, level);
	os << "<"  << name;
	writeAttributes(os);
	os << ">";

	if (txt != NULL)
	{
		os << escape(*txt);
	}
	else
	{
		writeChildElements(os, level + 1);
		writeIndentation(os, level);
	}

	os << "</" << name << ">" << std::endl;
}

///////////////////////////////////////////////////////////
void SimpleXMLBuilder::writeChildElements(std::ostream& os,
		int level) const
{
	os << std::endl;

	std::vector<SimpleXMLBuilder*>::const_iterator it;
	for (it = children.begin(); it < children.end(); it++)
		(*it)->writeElement(os, level);
}

///////////////////////////////////////////////////////////
void SimpleXMLBuilder::writeAttributes(std::ostream& os) const
{
	std::vector<Attribute*>::const_iterator it;
	for (it = attributes.begin(); it != attributes.end(); it++)
	{
		os << " " << (*it)->name << "=\"" << escape((*it)->value) << "\"";
	}
}

///////////////////////////////////////////////////////////
std::string SimpleXMLBuilder::escape(const std::string& str) const
{
	std::stringstream ss;

	const char* cstr = str.c_str();
	for (const char* c = cstr; *c; ++c)
	{
		switch (*c)
		{
			case '<':
				ss << "&lt;";
				break;
			case '>':
				ss << "&gt;";
				break;
			case '&':
				ss << "&amp;";
				break;
			case '\'':
				ss << "&apos;";
				break;
			case '"':
				ss << "&quot;";
				break;
			default:
				ss << *c;
				break;
		}
	}

	return ss.str();
}

///////////////////////////////////////////////////////////
void SimpleXMLBuilder::writeIndentation(std::ostream& os,
		int level) const
{
    static const std::string INDENTATION("  ");

	for(int i = 0; i < level; i++)
	{
		os << INDENTATION;
	}
}

///////////////////////////////////////////////////////////
XMLBuilder& SimpleXMLBuilder::element(const std::string& name)
{
	XMLBuilder* builder = new SimpleXMLBuilder(name, this);
	return *builder;
}

///////////////////////////////////////////////////////////
XMLBuilder& SimpleXMLBuilder::text(const std::string& text)
{
	if (txt != NULL)
		delete txt;

	txt = new std::string(text);
	return *this;
}

///////////////////////////////////////////////////////////
XMLBuilder& SimpleXMLBuilder::attribute(const std::string& name,
		const std::string& value)
{
	attributes.push_back(new Attribute(name, value));
	return *this;
}

///////////////////////////////////////////////////////////
XMLBuilder& SimpleXMLBuilder::up() const
{
	if (parent == NULL)
	{
		return const_cast<SimpleXMLBuilder&>(*this);
	}

	return *parent;
}

TESTNGPP_NS_END
