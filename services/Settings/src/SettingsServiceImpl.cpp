//
// SettingsServiceImpl.cpp
//
// Library: IoT/Settings
// Package: SettingsService
// Module:  SettingsServiceImpl
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Settings/SettingsServiceImpl.h"


using namespace std::string_literals;


namespace IoT {
namespace Settings {


SettingsServiceImpl::SettingsServiceImpl(Poco::Util::AbstractConfiguration::Ptr pGlobalConfig, Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pSettings, const std::string& settingsPath):
	_pConfig(pGlobalConfig),
	_pSettings(pSettings),
	_path(settingsPath)
{
}


SettingsServiceImpl::~SettingsServiceImpl()
{
}


Poco::Optional<std::string> SettingsServiceImpl::getString(const std::string& key, const Poco::Optional<std::string>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getString(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getString(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<Poco::Int16> SettingsServiceImpl::getInt16(const std::string& key, const Poco::Optional<Poco::Int16>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getInt16(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getInt16(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<Poco::UInt16> SettingsServiceImpl::getUInt16(const std::string& key, const Poco::Optional<Poco::UInt16>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getUInt16(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getUInt16(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<Poco::Int32> SettingsServiceImpl::getInt32(const std::string& key, const Poco::Optional<Poco::Int32>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getInt32(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getInt32(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<Poco::UInt32> SettingsServiceImpl::getUInt32(const std::string& key, const Poco::Optional<Poco::UInt32>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getUInt32(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getUInt32(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<Poco::Int64> SettingsServiceImpl::getInt64(const std::string& key, const Poco::Optional<Poco::Int64>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getInt64(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getInt64(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<Poco::UInt64> SettingsServiceImpl::getUInt64(const std::string& key, const Poco::Optional<Poco::UInt64>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getUInt64(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getUInt64(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<double> SettingsServiceImpl::getDouble(const std::string& key, const Poco::Optional<double>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getDouble(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getDouble(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


Poco::Optional<double> SettingsServiceImpl::getBool(const std::string& key, const Poco::Optional<double>& deflt) const
{
	if (deflt.isSpecified())
	{
		return _pConfig->getBool(key, deflt.value());
	}
	else
	{
		try
		{
			return _pConfig->getBool(key);
		}
		catch (Poco::NotFoundException&)
		{
		}
	}
	return {};
}


void SettingsServiceImpl::setString(const std::string& key, const std::string& value)
{
	_pSettings->setString(key, value);
}


void SettingsServiceImpl::setInt16(const std::string& key, Poco::Int16 value)
{
	_pSettings->setInt16(key, value);
}


void SettingsServiceImpl::setUInt16(const std::string& key, Poco::UInt16 value)
{
	_pSettings->setUInt16(key, value);
}


void SettingsServiceImpl::setInt32(const std::string& key, Poco::Int32 value)
{
	_pSettings->setInt32(key, value);
}


void SettingsServiceImpl::setUInt32(const std::string& key, Poco::UInt32 value)
{
	_pSettings->setUInt32(key, value);
}


void SettingsServiceImpl::setInt64(const std::string& key, Poco::Int64 value)
{
	_pSettings->setInt64(key, value);
}


void SettingsServiceImpl::setUInt64(const std::string& key, Poco::UInt64 value)
{
	_pSettings->setUInt64(key, value);
}


void SettingsServiceImpl::setDouble(const std::string& key, double value)
{
	_pSettings->setDouble(key, value);
}


void SettingsServiceImpl::setBool(const std::string& key, bool value)
{
	_pSettings->setBool(key, value);
}


std::vector<std::string> SettingsServiceImpl::keys(const std::string& key) const
{
	std::vector<std::string> result;
	_pConfig->keys(key, result);
	return result;
}


std::vector<std::string> SettingsServiceImpl::settingsKeys(const std::string& key) const
{
	std::vector<std::string> result;
	_pSettings->keys(key, result);
	return result;
}


bool SettingsServiceImpl::haveKey(const std::string& key) const
{
	return _pConfig->has(key);
}


bool SettingsServiceImpl::haveSettingsKey(const std::string& key) const
{
	return _pSettings->has(key);
}


void SettingsServiceImpl::remove(const std::string& key)
{
	_pSettings->remove(key);
}


void SettingsServiceImpl::save() const
{
	_pSettings->save(_path);
}


} } // namespace IoT::Settings
