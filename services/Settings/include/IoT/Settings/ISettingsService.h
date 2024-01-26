//
// ISettingsService.h
//
// Library: IoT/Settings
// Package: Generated
// Module:  ISettingsService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Settings_ISettingsService_INCLUDED
#define IoT_Settings_ISettingsService_INCLUDED


#include "IoT/Settings/SettingsService.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"


namespace IoT {
namespace Settings {


class ISettingsService: public Poco::OSP::Service
	/// The SettingsService provides a service interface to the
	/// configuration system. Specifically it allows to change
	/// configuration parameters and to save changed parameters
	/// in a file.
{
public:
	using Ptr = Poco::AutoPtr<ISettingsService>;

	ISettingsService();
		/// Creates a ISettingsService.

	virtual ~ISettingsService();
		/// Destroys the ISettingsService.

	virtual Poco::Optional < double > getBool(const std::string& key, const Poco::Optional < double >& deflt = Poco::Optional < double >()) const = 0;
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

	virtual Poco::Optional < double > getDouble(const std::string& key, const Poco::Optional < double >& deflt = Poco::Optional < double >()) const = 0;
		/// Returns the double value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to a double value.

	virtual Poco::Optional < Poco::Int16 > getInt16(const std::string& key, const Poco::Optional < Poco::Int16 >& deflt = Poco::Optional < Poco::Int16 >()) const = 0;
		/// Returns the 16-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an Int16 value.

	virtual Poco::Optional < Poco::Int32 > getInt32(const std::string& key, const Poco::Optional < Poco::Int32 >& deflt = Poco::Optional < Poco::Int32 >()) const = 0;
		/// Returns the 32-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an Int32 value.

	virtual Poco::Optional < Poco::Int64 > getInt64(const std::string& key, const Poco::Optional < Poco::Int64 >& deflt = Poco::Optional < Poco::Int64 >()) const = 0;
		/// Returns the 64-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to an Int64 value.

	virtual Poco::Optional < std::string > getString(const std::string& key, const Poco::Optional < std::string >& deflt = Poco::Optional < std::string >()) const = 0;
		/// Returns the string value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.

	virtual Poco::Optional < Poco::UInt16 > getUInt16(const std::string& key, const Poco::Optional < Poco::UInt16 >& deflt = Poco::Optional < Poco::UInt16 >()) const = 0;
		/// Returns the 16-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt16 value.

	virtual Poco::Optional < Poco::UInt32 > getUInt32(const std::string& key, const Poco::Optional < Poco::UInt32 >& deflt = Poco::Optional < Poco::UInt32 >()) const = 0;
		/// Returns the 32-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt32 value.

	virtual Poco::Optional < Poco::UInt64 > getUInt64(const std::string& key, const Poco::Optional < Poco::UInt64 >& deflt = Poco::Optional < Poco::UInt64 >()) const = 0;
		/// Returns the 64-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt64 value.

	virtual bool haveKey(const std::string& key) const = 0;
		/// Returns true if the given key exists (either in the settings configuration,
		/// or in the global configuration), otherwise false.

	virtual bool haveSettingsKey(const std::string& key) const = 0;
		/// Returns true if the given key is defined in the settings configuration
		/// object, otherwise false.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::vector < std::string > keys(const std::string& key = std::string()) const = 0;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void remove(const std::string& key) = 0;
		/// Removes the value with the given key from the settings configuration.

	virtual void save() const = 0;
		/// Saves the settings file to disk.

	virtual void setBool(const std::string& key, bool value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setDouble(const std::string& key, double value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt16(const std::string& key, Poco::Int16 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt32(const std::string& key, Poco::Int32 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt64(const std::string& key, Poco::Int64 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setString(const std::string& key, const std::string& value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt16(const std::string& key, Poco::UInt16 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt32(const std::string& key, Poco::UInt32 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt64(const std::string& key, Poco::UInt64 value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual std::vector < std::string > settingsKeys(const std::string& key = std::string()) const = 0;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.
		///
		/// Only keys from the underlying settings configuration object are 
		/// returned.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace Settings
} // namespace IoT


#endif // IoT_Settings_ISettingsService_INCLUDED

