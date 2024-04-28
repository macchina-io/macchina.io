//
// Preferences.cpp
//
// Library: OSP
// Package: PreferencesService
// Module:  Preferences
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Preferences.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include "Poco/File.h"


using Poco::FastMutex;


namespace Poco {
namespace OSP {


Preferences::Preferences(const std::string& path):
	_path(path),
	_pConfig(new Poco::Util::PropertyFileConfiguration()),
	_dirty(false)
{
	Poco::Path p(path);
	Poco::Path pp(p.parent());
	File pf(pp);
	if (!pf.exists())
	{
		pf.createDirectories();
	}
	File f(p);
	if (f.exists())
	{
		_pConfig->load(_path);
	}
}


Preferences::~Preferences()
{
	try
	{
		try
		{
			save();
		}
		catch (Poco::Exception& exc)
		{
			Logger::get(PreferencesService::SERVICE_NAME).error(std::string("Failed to save preferences: ")
				+ exc.displayText());
		}
		_pConfig->release();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void Preferences::save()
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (_dirty)
	{
		_pConfig->save(_path);
		_dirty = false;
	}
}


bool Preferences::getRaw(const std::string& key, std::string& value) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (_pConfig->hasProperty(key))
	{
		value = _pConfig->getRawString(key);
		return true;
	}
	else return false;
}


void Preferences::setRaw(const std::string& key, const std::string& value)		
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string oldValue;
	if (_pConfig->hasProperty(key))
		oldValue = _pConfig->getRawString(key);

	PreferencesEvent propertyChangedEvent(key, oldValue, value);
	propertyChanged(this, propertyChangedEvent);

	_pConfig->setString(key, value);
	_dirty = true;
}


void Preferences::enumerate(const std::string& key, Keys& range) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _pConfig->keys(key, range);
}


void Preferences::removeRaw(const std::string& key)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_pConfig->remove(key);
	_dirty = true;
}


} } // namespace Poco::OSP
