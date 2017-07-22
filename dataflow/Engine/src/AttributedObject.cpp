//
// AttributedObject.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Node
// Module:  Node
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/AttributedObject.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


AttributedObject::AttributedObject()
{
}


AttributedObject::AttributedObject(const AttributedObject& other):
	_attributes(other._attributes)
{
}

	
AttributedObject& AttributedObject::operator = (const AttributedObject& other)
{
	_attributes = other._attributes;
	return *this;
}


AttributedObject::~AttributedObject()
{
}

	
void AttributedObject::setAttribute(const std::string& name, const std::string& value)
{
	_attributes[name] = value;
}


void AttributedObject::setAttribute(const std::string& name, int value)
{
	_attributes[name] = Poco::NumberFormatter::format(value);
}


void AttributedObject::setAttribute(const std::string& name, double value)
{
	_attributes[name] = Poco::NumberFormatter::format(value);
}


void AttributedObject::setAttribute(const std::string& name, bool value)
{
	_attributes[name] = Poco::NumberFormatter::format(value);
}


const std::string& AttributedObject::getAttribute(const std::string& name) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return it->second;
	else
		throw Poco::NotFoundException(name);
}

	
const std::string& AttributedObject::getAttribute(const std::string& name, const std::string& deflt) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return it->second;
	else
		return deflt;
}


int AttributedObject::getIntAttribute(const std::string& name) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return Poco::NumberParser::parse(it->second);
	else
		throw Poco::NotFoundException(name);
}


int AttributedObject::getIntAttribute(const std::string& name, int deflt) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return Poco::NumberParser::parse(it->second);
	else
		return deflt;
}


double AttributedObject::getDoubleAttribute(const std::string& name) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return Poco::NumberParser::parseFloat(it->second);
	else
		throw Poco::NotFoundException(name);
}


double AttributedObject::getDoubleAttribute(const std::string& name, double deflt) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return Poco::NumberParser::parseFloat(it->second);
	else
		return deflt;
}


bool AttributedObject::getBoolAttribute(const std::string& name) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return Poco::NumberParser::parseBool(it->second);
	else
		throw Poco::NotFoundException(name);
}


bool AttributedObject::getBoolAttribute(const std::string& name, bool deflt) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return Poco::NumberParser::parseBool(it->second);
	else
		return deflt;
}


bool AttributedObject::hasAttribute(const std::string& name) const
{
	NameValueMap::const_iterator it = _attributes.find(name);
	return it != _attributes.end();
}


void AttributedObject::removeAttribute(const std::string& name)
{
	_attributes.erase(name);
}


std::vector<std::string> AttributedObject::enumerateAttributes() const
{
	std::vector<std::string> result;
	for (NameValueMap::const_iterator it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		result.push_back(it->first);
	}
	
	return result;
}


void AttributedObject::clearAttributes()
{
	_attributes.clear();
}


} } } // namespace IoT::Dataflow::Engine
