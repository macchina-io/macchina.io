//
// Configuration.cpp
//
// Library: OSP
// Package: PreferencesService
// Module:  Configuration
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Configuration.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


Configuration::Configuration(AbstractConfiguration* pConfig):
	_pConfig(pConfig)
{
	poco_check_ptr (pConfig);
	
	_pConfig->duplicate();
}


Configuration::~Configuration()
{
	_pConfig->release();
}


bool Configuration::getRaw(const std::string& key, std::string& value) const
{
	if (_pConfig->hasProperty(key))
	{
		value = _pConfig->getRawString(key);
		return true;
	}
	else return false;
}


void Configuration::setRaw(const std::string& key, const std::string& value)		
{
	throw Poco::InvalidAccessException("Cannot change configuration properties");
}


void Configuration::enumerate(const std::string& key, Keys& range) const
{
	_pConfig->keys(key, range);
}


void Configuration::removeRaw(const std::string& key)
{
	throw Poco::InvalidAccessException("Cannot change configuration properties");
}


} } // namespace Poco::OSP
