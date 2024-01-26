//
// SettingsService.h
//
// Library: IoT/Settings
// Package: SettingsService
// Module:  SettingsService
//
// Definition of the SettingsService interface.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Settings_SettingsService_INCLUDED
#define IoT_Settings_SettingsService_INCLUDED


#include "IoT/Settings/Settings.h"
#include "Poco/SharedPtr.h"
#include "Poco/Types.h"
#include "Poco/Optional.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Settings {


//@ serialize
struct KeyValue
{
	std::string key;
	std::string value;
};


//@ remote
class IoTSettings_API SettingsService
	/// The SettingsService provides a service interface to the
	/// configuration system. Specifically it allows to change
	/// configuration parameters and to save changed parameters
	/// in a file.
{
public:
	using Ptr = Poco::SharedPtr<SettingsService>;

	SettingsService();
		/// Creates the SettingsService.

	virtual ~SettingsService();
		/// Destroys the SettingsService.

	//@ $deflt={optional}
	virtual Poco::Optional<std::string> getString(const std::string& key, const Poco::Optional<std::string>& deflt = Poco::Optional<std::string>()) const = 0;
		/// Returns the string value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.

	//@ $deflt={optional}
	virtual Poco::Optional<Poco::Int16> getInt16(const std::string& key, const Poco::Optional<Poco::Int16>& deflt = Poco::Optional<Poco::Int16>()) const = 0;
		/// Returns the 16-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an Int16 value.

	//@ $deflt={optional}
	virtual Poco::Optional<Poco::UInt16> getUInt16(const std::string& key, const Poco::Optional<Poco::UInt16>& deflt = Poco::Optional<Poco::UInt16>()) const = 0;
		/// Returns the 16-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt16 value.

	//@ $deflt={optional}
	virtual Poco::Optional<Poco::Int32> getInt32(const std::string& key, const Poco::Optional<Poco::Int32>& deflt = Poco::Optional<Poco::Int32>()) const = 0;
		/// Returns the 32-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an Int32 value.

	//@ $deflt={optional}
	virtual Poco::Optional<Poco::UInt32> getUInt32(const std::string& key, const Poco::Optional<Poco::UInt32>& deflt = Poco::Optional<Poco::UInt32>()) const = 0;
		/// Returns the 32-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt32 value.

	//@ $deflt={optional}
	virtual Poco::Optional<Poco::Int64> getInt64(const std::string& key, const Poco::Optional<Poco::Int64>& deflt = Poco::Optional<Poco::Int64>()) const = 0;
		/// Returns the 64-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to an Int64 value.

	//@ $deflt={optional}
	virtual Poco::Optional<Poco::UInt64> getUInt64(const std::string& key, const Poco::Optional<Poco::UInt64>& deflt = Poco::Optional<Poco::UInt64>()) const = 0;
		/// Returns the 64-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt64 value.

	//@ $deflt={optional}
	virtual Poco::Optional<double> getDouble(const std::string& key, const Poco::Optional<double>& deflt = Poco::Optional<double>()) const = 0;
		/// Returns the double value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to a double value.

	//@ $deflt={optional}
	virtual Poco::Optional<double> getBool(const std::string& key, const Poco::Optional<double>& deflt = Poco::Optional<double>()) const = 0;
		/// Returns the boolean value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to a boolean value.
		///
		/// The following string values can be converted into a boolean:
		///   - numerical values: non-zero becomes true, zero becomes false
		///   - strings: "true", "yes", "on" become true, "false", "no", "off" become false
		/// Case does not matter.

	virtual void setString(const std::string& key, const std::string& value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt16(const std::string& key, Poco::Int16 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt16(const std::string& key, Poco::UInt16 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt32(const std::string& key, Poco::Int32 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt32(const std::string& key, Poco::UInt32 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt64(const std::string& key, Poco::Int64 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt64(const std::string& key, Poco::UInt64 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setDouble(const std::string& key, double value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setBool(const std::string& key, bool value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	//@ $key={optional}
	virtual std::vector<std::string> keys(const std::string& key = std::string()) const = 0;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.

	//@ $key={optional}
	virtual std::vector<std::string> settingsKeys(const std::string& key = std::string()) const = 0;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.
		///
		/// Only keys from the underlying settings configuration object are 
		/// returned.

	virtual bool haveKey(const std::string& key) const = 0;
		/// Returns true if the given key exists (either in the settings configuration,
		/// or in the global configuration), otherwise false.

	virtual bool haveSettingsKey(const std::string& key) const = 0;
		/// Returns true if the given key is defined in the settings configuration
		/// object, otherwise false.

	virtual void remove(const std::string& key) = 0;
		/// Removes the value with the given key from the settings configuration.

	virtual void save() const = 0;
		/// Saves the settings file to disk.
};


} } // namespace IoT::Settings


#endif // IoT_Settings_SettingsService_INCLUDED
