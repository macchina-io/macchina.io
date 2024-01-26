//
// SettingsServiceImpl.h
//
// Library: IoT/Settings
// Package: SettingsService
// Module:  SettingsServiceImpl
//
// Definition of the SettingsServiceImpl class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Settings_SettingsServiceImpl_INCLUDED
#define IoT_Settings_SettingsServiceImpl_INCLUDED


#include "IoT/Settings/SettingsService.h"
#include "Poco/Util/PropertyFileConfiguration.h"


namespace IoT {
namespace Settings {


class IoTSettings_API SettingsServiceImpl: public SettingsService
	/// Implementation of SettingService.
{
public:
	using Ptr = Poco::SharedPtr<SettingsServiceImpl>;

	SettingsServiceImpl(Poco::Util::AbstractConfiguration::Ptr pGlobalConfiguration, Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pSettings, const std::string& settingsPath);
		/// Creates the SettingsServiceImpl, using the
		/// given global configuration.

	~SettingsServiceImpl();
		/// Destroys the SettingsServiceImpl.

	// SettingsService
	Poco::Optional<std::string> getString(const std::string& key, const Poco::Optional<std::string>& deflt) const;
	Poco::Optional<Poco::Int16> getInt16(const std::string& key, const Poco::Optional<Poco::Int16>& deflt) const;
	Poco::Optional<Poco::UInt16> getUInt16(const std::string& key, const Poco::Optional<Poco::UInt16>& deflt) const;
	Poco::Optional<Poco::Int32> getInt32(const std::string& key, const Poco::Optional<Poco::Int32>& deflt) const;
	Poco::Optional<Poco::UInt32> getUInt32(const std::string& key, const Poco::Optional<Poco::UInt32>& deflt) const;
	Poco::Optional<Poco::Int64> getInt64(const std::string& key, const Poco::Optional<Poco::Int64>& deflt) const;
	Poco::Optional<Poco::UInt64> getUInt64(const std::string& key, const Poco::Optional<Poco::UInt64>& deflt) const;
	Poco::Optional<double> getDouble(const std::string& key, const Poco::Optional<double>& deflt) const;
	Poco::Optional<double> getBool(const std::string& key, const Poco::Optional<double>& deflt) const;
	void setString(const std::string& key, const std::string& value);
	void setInt16(const std::string& key, Poco::Int16 value);
	void setUInt16(const std::string& key, Poco::UInt16 value);
	void setInt32(const std::string& key, Poco::Int32 value);
	void setUInt32(const std::string& key, Poco::UInt32 value);
	void setInt64(const std::string& key, Poco::Int64 value);
	void setUInt64(const std::string& key, Poco::UInt64 value);
	void setDouble(const std::string& key, double value);
	void setBool(const std::string& key, bool value);
	std::vector<std::string> keys(const std::string& key) const;
	std::vector<std::string> settingsKeys(const std::string& key) const;
	bool haveKey(const std::string& key) const;
	bool haveSettingsKey(const std::string& key) const;
	void remove(const std::string& key);
	void save() const;

private:
	Poco::Util::AbstractConfiguration::Ptr _pConfig;
	Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> _pSettings;
	const std::string _path;
};


} } // namespace IoT::Settings


#endif // IoT_Settings_SettingsServiceImpl_INCLUDED
