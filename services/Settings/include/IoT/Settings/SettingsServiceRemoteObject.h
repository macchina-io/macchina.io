//
// SettingsServiceRemoteObject.h
//
// Library: IoT/Settings
// Package: Generated
// Module:  SettingsServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Settings_SettingsServiceRemoteObject_INCLUDED
#define IoT_Settings_SettingsServiceRemoteObject_INCLUDED


#include "IoT/Settings/ISettingsService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Settings {


class SettingsServiceRemoteObject: public IoT::Settings::ISettingsService, public Poco::RemotingNG::RemoteObject
	/// The SettingsService provides a service interface to the
	/// configuration system. Specifically it allows to change
	/// configuration parameters and to save changed parameters
	/// in a file.
{
public:
	using Ptr = Poco::AutoPtr<SettingsServiceRemoteObject>;

	SettingsServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Settings::SettingsService> pServiceObject);
		/// Creates a SettingsServiceRemoteObject.

	virtual ~SettingsServiceRemoteObject();
		/// Destroys the SettingsServiceRemoteObject.

	virtual Poco::Optional < double > getBool(const std::string& key, const Poco::Optional < double >& deflt = Poco::Optional < double >()) const;
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

	virtual Poco::Optional < double > getDouble(const std::string& key, const Poco::Optional < double >& deflt = Poco::Optional < double >()) const;
		/// Returns the double value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to a double value.

	virtual Poco::Optional < Poco::Int16 > getInt16(const std::string& key, const Poco::Optional < Poco::Int16 >& deflt = Poco::Optional < Poco::Int16 >()) const;
		/// Returns the 16-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an Int16 value.

	virtual Poco::Optional < Poco::Int32 > getInt32(const std::string& key, const Poco::Optional < Poco::Int32 >& deflt = Poco::Optional < Poco::Int32 >()) const;
		/// Returns the 32-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an Int32 value.

	virtual Poco::Optional < Poco::Int64 > getInt64(const std::string& key, const Poco::Optional < Poco::Int64 >& deflt = Poco::Optional < Poco::Int64 >()) const;
		/// Returns the 64-bit integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException if the property value 
		/// can not be converted to an Int64 value.

	virtual Poco::Optional < std::string > getString(const std::string& key, const Poco::Optional < std::string >& deflt = Poco::Optional < std::string >()) const;
		/// Returns the string value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.

	virtual Poco::Optional < Poco::UInt16 > getUInt16(const std::string& key, const Poco::Optional < Poco::UInt16 >& deflt = Poco::Optional < Poco::UInt16 >()) const;
		/// Returns the 16-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt16 value.

	virtual Poco::Optional < Poco::UInt32 > getUInt32(const std::string& key, const Poco::Optional < Poco::UInt32 >& deflt = Poco::Optional < Poco::UInt32 >()) const;
		/// Returns the 32-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt32 value.

	virtual Poco::Optional < Poco::UInt64 > getUInt64(const std::string& key, const Poco::Optional < Poco::UInt64 >& deflt = Poco::Optional < Poco::UInt64 >()) const;
		/// Returns the 64-bit unsigned integer value of the property with the given key,
		/// or the given default value if the key does not exist. 
		/// If the value contains references to other properties (${<property>}, or
		/// ${<property>:-<default>}), these are expanded.
		///
		/// Throws a Poco::SyntaxException or a Poco::RangeException if the property value 
		/// can not be converted to an UInt64 value.

	virtual bool haveKey(const std::string& key) const;
		/// Returns true if the given key exists (either in the settings configuration,
		/// or in the global configuration), otherwise false.

	virtual bool haveSettingsKey(const std::string& key) const;
		/// Returns true if the given key is defined in the settings configuration
		/// object, otherwise false.

	virtual std::vector < std::string > keys(const std::string& key = std::string()) const;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void remove(const std::string& key);
		/// Removes the value with the given key from the settings configuration.

	virtual void save() const;
		/// Saves the settings file to disk.

	virtual void setBool(const std::string& key, bool value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setDouble(const std::string& key, double value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt16(const std::string& key, Poco::Int16 value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt32(const std::string& key, Poco::Int32 value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setInt64(const std::string& key, Poco::Int64 value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setString(const std::string& key, const std::string& value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt16(const std::string& key, Poco::UInt16 value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt32(const std::string& key, Poco::UInt32 value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual void setUInt64(const std::string& key, Poco::UInt64 value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// The new value is not persisted. Call save() to persist changes.

	virtual std::vector < std::string > settingsKeys(const std::string& key = std::string()) const;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.
		///
		/// Only keys from the underlying settings configuration object are 
		/// returned.

private:
	Poco::SharedPtr<IoT::Settings::SettingsService> _pServiceObject;
};


inline Poco::Optional < double > SettingsServiceRemoteObject::getBool(const std::string& key, const Poco::Optional < double >& deflt) const
{
	return _pServiceObject->getBool(key, deflt);
}


inline Poco::Optional < double > SettingsServiceRemoteObject::getDouble(const std::string& key, const Poco::Optional < double >& deflt) const
{
	return _pServiceObject->getDouble(key, deflt);
}


inline Poco::Optional < Poco::Int16 > SettingsServiceRemoteObject::getInt16(const std::string& key, const Poco::Optional < Poco::Int16 >& deflt) const
{
	return _pServiceObject->getInt16(key, deflt);
}


inline Poco::Optional < Poco::Int32 > SettingsServiceRemoteObject::getInt32(const std::string& key, const Poco::Optional < Poco::Int32 >& deflt) const
{
	return _pServiceObject->getInt32(key, deflt);
}


inline Poco::Optional < Poco::Int64 > SettingsServiceRemoteObject::getInt64(const std::string& key, const Poco::Optional < Poco::Int64 >& deflt) const
{
	return _pServiceObject->getInt64(key, deflt);
}


inline Poco::Optional < std::string > SettingsServiceRemoteObject::getString(const std::string& key, const Poco::Optional < std::string >& deflt) const
{
	return _pServiceObject->getString(key, deflt);
}


inline Poco::Optional < Poco::UInt16 > SettingsServiceRemoteObject::getUInt16(const std::string& key, const Poco::Optional < Poco::UInt16 >& deflt) const
{
	return _pServiceObject->getUInt16(key, deflt);
}


inline Poco::Optional < Poco::UInt32 > SettingsServiceRemoteObject::getUInt32(const std::string& key, const Poco::Optional < Poco::UInt32 >& deflt) const
{
	return _pServiceObject->getUInt32(key, deflt);
}


inline Poco::Optional < Poco::UInt64 > SettingsServiceRemoteObject::getUInt64(const std::string& key, const Poco::Optional < Poco::UInt64 >& deflt) const
{
	return _pServiceObject->getUInt64(key, deflt);
}


inline bool SettingsServiceRemoteObject::haveKey(const std::string& key) const
{
	return _pServiceObject->haveKey(key);
}


inline bool SettingsServiceRemoteObject::haveSettingsKey(const std::string& key) const
{
	return _pServiceObject->haveSettingsKey(key);
}


inline std::vector < std::string > SettingsServiceRemoteObject::keys(const std::string& key) const
{
	return _pServiceObject->keys(key);
}


inline const Poco::RemotingNG::Identifiable::TypeId& SettingsServiceRemoteObject::remoting__typeId() const
{
	return ISettingsService::remoting__typeId();
}


inline void SettingsServiceRemoteObject::remove(const std::string& key)
{
	_pServiceObject->remove(key);
}


inline void SettingsServiceRemoteObject::save() const
{
	_pServiceObject->save();
}


inline void SettingsServiceRemoteObject::setBool(const std::string& key, bool value)
{
	_pServiceObject->setBool(key, value);
}


inline void SettingsServiceRemoteObject::setDouble(const std::string& key, double value)
{
	_pServiceObject->setDouble(key, value);
}


inline void SettingsServiceRemoteObject::setInt16(const std::string& key, Poco::Int16 value)
{
	_pServiceObject->setInt16(key, value);
}


inline void SettingsServiceRemoteObject::setInt32(const std::string& key, Poco::Int32 value)
{
	_pServiceObject->setInt32(key, value);
}


inline void SettingsServiceRemoteObject::setInt64(const std::string& key, Poco::Int64 value)
{
	_pServiceObject->setInt64(key, value);
}


inline void SettingsServiceRemoteObject::setString(const std::string& key, const std::string& value)
{
	_pServiceObject->setString(key, value);
}


inline void SettingsServiceRemoteObject::setUInt16(const std::string& key, Poco::UInt16 value)
{
	_pServiceObject->setUInt16(key, value);
}


inline void SettingsServiceRemoteObject::setUInt32(const std::string& key, Poco::UInt32 value)
{
	_pServiceObject->setUInt32(key, value);
}


inline void SettingsServiceRemoteObject::setUInt64(const std::string& key, Poco::UInt64 value)
{
	_pServiceObject->setUInt64(key, value);
}


inline std::vector < std::string > SettingsServiceRemoteObject::settingsKeys(const std::string& key) const
{
	return _pServiceObject->settingsKeys(key);
}


} // namespace Settings
} // namespace IoT


#endif // IoT_Settings_SettingsServiceRemoteObject_INCLUDED

