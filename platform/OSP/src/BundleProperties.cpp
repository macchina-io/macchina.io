//
// BundleProperties.cpp
//
// $Id: //poco/1.7/OSP/src/BundleProperties.cpp#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleProperties
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleProperties.h"


namespace Poco {
namespace OSP {


BundleProperties::BundleProperties():
	_pLayeredConfig(new Poco::Util::LayeredConfiguration)
{
}


BundleProperties::~BundleProperties()
{
	_pLayeredConfig->release();
}


void BundleProperties::addProperties(Poco::Util::AbstractConfiguration* pConfig, bool shared)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_pLayeredConfig->add(pConfig, shared);
}

	
void BundleProperties::addProperties(Poco::Util::AbstractConfiguration* pConfig, int priority, bool shared)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_pLayeredConfig->add(pConfig, priority, shared);
}


void BundleProperties::removeProperties(Poco::Util::AbstractConfiguration* pConfig)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_pLayeredConfig->removeConfiguration(pConfig);
}


bool BundleProperties::getRaw(const std::string& key, std::string& value) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (_pLayeredConfig->hasProperty(key))
	{
		value = _pLayeredConfig->getRawString(key);
		return true;
	}
	else return false;
}


void BundleProperties::setRaw(const std::string& key, const std::string& value)
{
	throw Poco::InvalidAccessException("Cannot change bundle properties");
}


void BundleProperties::enumerate(const std::string& key, Keys& range) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_pLayeredConfig->keys(key, range);
}


void BundleProperties::removeRaw(const std::string& key)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_pLayeredConfig->remove(key);
}


} } // namespace Poco::OSP
