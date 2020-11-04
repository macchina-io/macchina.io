//
// Properties.cpp
//
// Library: OSP
// Package: Util
// Module:  Properties
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Properties.h"
#include "Poco/Exception.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include <algorithm>


using Poco::NumberParser;


namespace Poco {
namespace OSP {


const std::string Properties::PROP_TRUE("true");
const std::string Properties::PROP_FALSE("false");


Properties::Properties()
{
}


Properties::Properties(const Properties& props):
	_props(props._props)
{
}


Properties::~Properties()
{
}


Properties& Properties::operator = (const Properties& props)
{
	Properties tmp(props);
	swap(tmp);
	return *this;
}


void Properties::swap(Properties& props)
{
	std::swap(_props, props._props);
}


std::string Properties::get(const std::string& key) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return it->second;
	else
		throw NotFoundException(key);
}


std::string Properties::get(const std::string& key, const std::string& deflt) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return it->second;
	else
		return deflt;
}


bool Properties::getBool(const std::string& key) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return it->second != PROP_FALSE;
	else
		throw NotFoundException(key);
}


bool Properties::getBool(const std::string& key, bool deflt) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return it->second != PROP_FALSE;
	else
		return deflt;
}


int Properties::getInt(const std::string& key) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return NumberParser::parse(it->second);
	else
		throw NotFoundException(key);
}


int Properties::getInt(const std::string& key, int deflt) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return NumberParser::parse(it->second);
	else
		return deflt;
}


Poco::Int64 Properties::getInt64(const std::string& key) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return NumberParser::parse64(it->second);
	else
		throw NotFoundException(key);
}


Poco::Int64 Properties::getInt64(const std::string& key, Poco::Int64 deflt) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return NumberParser::parse64(it->second);
	else
		return deflt;
}


double Properties::getFloat(const std::string& key) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return NumberParser::parseFloat(it->second);
	else
		throw NotFoundException(key);
}


double Properties::getFloat(const std::string& key, double deflt) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	PropsMap::const_iterator it = _props.find(key);
	if (it != _props.end())
		return NumberParser::parseFloat(it->second);
	else
		return deflt;
}


void Properties::set(const std::string& key, const std::string& value)
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	_props[key] = value;
}


void Properties::set(const std::string& key, const char* value)
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	_props[key] = value;
}


void Properties::set(const std::string& key, bool value)
{
	set(key, value ? PROP_TRUE : PROP_FALSE);
}


void Properties::set(const std::string& key, int value)
{
	set(key, NumberFormatter::format(value));
}


void Properties::set(const std::string& key, Poco::Int64 value)
{
	set(key, NumberFormatter::format(value));
}


void Properties::set(const std::string& key, double value)
{
	set(key, NumberFormatter::format(value));
}


bool Properties::has(const std::string& key) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	return _props.find(key) != _props.end();
}


void Properties::keys(std::vector<std::string>& keys) const
{
	Poco::FastMutex::ScopedLock _lock(_mutex);

	keys.clear();
	keys.reserve(_props.size());
	for (PropsMap::const_iterator it = _props.begin(); it != _props.end(); ++it)
	{
		keys.push_back(it->first);
	}
}


} } // namespace Poco::OSP
