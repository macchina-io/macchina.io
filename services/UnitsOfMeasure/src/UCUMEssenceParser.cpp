//
// UCUMEssenceParser.cpp
//
// Library: IoT/UnitsOfMeasure
// Package: UnitsOfMeasure
// Module:  UCUMEssenceParser
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/UnitsOfMeasure/UCUMEssenceParser.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceImpl.h"
#include "Poco/SAX/SAXParser.h"
#include "Poco/SAX/DefaultHandler.h"
#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/NumberParser.h"
#include "Poco/String.h"
#include <map>


namespace IoT {
namespace UnitsOfMeasure {


class UCUMEssenceHandler: public Poco::XML::DefaultHandler
{
public:
	UCUMEssenceHandler(UnitsOfMeasureServiceImpl& uoms):
		_uoms(uoms)
	{
	}

	void startElement(const Poco::XML::XMLString& uri, const Poco::XML::XMLString& localName, const Poco::XML::XMLString& qname, const Poco::XML::Attributes& attributes)
	{
		if (localName == "prefix" || localName == "base-unit" || localName == "unit")
		{
			clear();
		}
		if (isMarkup(localName))
		{
			_chars += "<";
			_chars += localName;
			_chars += ">";
		}
		else
		{
			storeAttributes(localName, attributes);
		}
	}

	void endElement(const Poco::XML::XMLString& uri, const Poco::XML::XMLString& localName, const Poco::XML::XMLString& qname)
	{
		if (localName == "prefix")
		{
			addPrefix();
		}
		else if (localName == "base-unit")
		{
			addBaseUnit();
		}
		else if (localName == "unit")
		{
			addUnit();
		}
		if (isMarkup(localName))
		{
			_chars += "</";
			_chars += localName;
			_chars += ">";
		}
		else
		{
			storeContent(localName, _chars);
		}
	}

	void characters(const Poco::XML::XMLChar ch[], int start, int length)
	{
		_chars.append(ch + start, length);
	}

	void clear()
	{
		_chars.clear();
		_attrs.clear();
	}

	void storeAttributes(const std::string& elem, const Poco::XML::Attributes& attributes)
	{
		for (int i = 0; i < attributes.getLength(); i++)
		{
			std::string key(elem);
			key += "/";
			key += attributes.getLocalName(i);
			_attrs[key] = attributes.getValue(i);
		}
	}

	void storeContent(const std::string& elem, const std::string& content)
	{
		Poco::trimInPlace(_chars);
		_attrs[elem] = (_chars);
		_chars.clear();
	}

	bool isMarkup(const std::string& localName) const
	{
		return
			localName == "i" ||
			localName == "r" ||
			localName == "sup" ||
			localName == "sub";
	}

	void addPrefix()
	{
		Prefix p;
		p.code  = getString("prefix/Code");
		p.icode = getString("prefix/CODE");
		p.name  = getString("name");
		p.print = getString("printSymbol");
		p.value = getDouble("value/value");
		_uoms.addPrefix(p);
	}

	void addBaseUnit()
	{
		Unit u;
		u.code     = getString("base-unit/Code");
		u.icode    = getString("base-unit/CODE");
		u.dim      = getString("base-unit/dim");
		u.name     = getString("name");
		u.print    = getString("printSymbol");
		u.property = getString("property");
		_uoms.addUnit(u);
	}

	void addUnit()
	{
		Unit u;
		u.code     = getString("unit/Code");
		u.icode    = getString("unit/CODE");
		u.metric   = getString("unit/isMetric") == "yes";
		u.group    = getString("unit/class");
		u.name     = getString("name");
		u.print    = getString("printSymbol");
		u.property = getString("property");
		u.unit     = getString("value/Unit");
		u.iunit    = getString("value/UNIT");
		u.value    = getDouble("value/value");
		_uoms.addUnit(u);
	}

	std::string getString(const std::string& key) const
	{
		std::map<std::string, std::string>::const_iterator it = _attrs.find(key);
		if (it != _attrs.end())
			return it->second;
		else
			return std::string();
	}

	double getDouble(const std::string& key) const
	{
		std::map<std::string, std::string>::const_iterator it = _attrs.find(key);
		if (it != _attrs.end())
			return Poco::NumberParser::parseFloat(it->second);
		else
			return 0;
	}

private:
	UnitsOfMeasureServiceImpl& _uoms;
	std::string _chars;
	std::map<std::string, std::string> _attrs;
};


UCUMEssenceParser::UCUMEssenceParser(UnitsOfMeasureServiceImpl& uoms):
	_uoms(uoms)
{
}


UCUMEssenceParser::~UCUMEssenceParser()
{
}


void UCUMEssenceParser::parse(std::istream& istr)
{
	UCUMEssenceHandler handler(_uoms);
	Poco::XML::SAXParser parser;
	parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, true);
	parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACE_PREFIXES, true);
	parser.setContentHandler(&handler);
	Poco::XML::InputSource src(istr);
	parser.parse(&src);
}


} } // namespace IoT::UnitsOfMeasure
