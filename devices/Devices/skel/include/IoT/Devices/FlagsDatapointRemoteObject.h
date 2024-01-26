//
// FlagsDatapointRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  FlagsDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_FlagsDatapointRemoteObject_INCLUDED
#define IoT_Devices_FlagsDatapointRemoteObject_INCLUDED


#include "IoT/Devices/IFlagsDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class FlagsDatapointRemoteObject: public IoT::Devices::IFlagsDatapoint, public Poco::RemotingNG::RemoteObject
	/// The base class for datapoints holding a variable number of
	/// flag bits, internally stored as a std::vector<bool>.
	///
	/// An implementation should handle conversion between a
	/// flag bit and the corresponding symbolic name of
	/// a flag.
	///
	/// In addition to the methods defined in this interface,
	/// a FlagsDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Ptr = Poco::AutoPtr<FlagsDatapointRemoteObject>;

	FlagsDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject);
		/// Creates a FlagsDatapointRemoteObject.

	virtual ~FlagsDatapointRemoteObject();
		/// Destroys the FlagsDatapointRemoteObject.

	std::vector < IoT::Devices::FlagValue > definedFlags() const;
		/// Returns a vector containing the possible flags
		/// and mappings to symbolic names.

	virtual std::vector < std::string > flags() const;
		/// Returns a vector containing the symbolic names
		/// of all flags currently set, even if the datapoint
		/// has been invalidated.
		///
		/// Use validFlags() to get a valid value only.

	virtual bool getFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.

	virtual bool getPropertyBool(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual double getPropertyDouble(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual int getPropertyInt(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual Poco::Int16 getPropertyInt16(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual Poco::Int64 getPropertyInt64(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual std::string getPropertyString(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual Poco::Timestamp getPropertyTimestamp(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual bool hasFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.

	virtual bool hasProperty(const std::string& name) const;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.

	virtual void invalidate();
		/// Invalidates the datapoint's value.
		///
		/// Subsequent calls to valid() will return false,
		/// until a new value has been set.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	std::vector < bool > reset(std::vector < bool > value = std::vector < bool >());
		/// Resets all flags to zero or the given value.
		/// Also makes the datapoint valid.
		///
		/// Returns the previously set flags.

	virtual void resetFlags(const std::vector < std::string >& flags = std::vector < std::string >());
		/// Resets all flags to the given set of flags and
		/// makes the datapoint valid.

	std::vector < bool > set(std::vector < bool > flags);
		/// Sets flags by logically OR-ing the currently set flags with the given ones.
		///
		/// Returns the previously set flags.

	virtual void setFeature(const std::string& name, bool enable);
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

	virtual void setFlags(const std::vector < std::string >& flags);
		/// Sets flags by logically OR-ing the currently set flags with the given ones.

	virtual void setPropertyBool(const std::string& name, bool value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyDouble(const std::string& name, double value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt(const std::string& name, int value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt16(const std::string& name, Poco::Int16 value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt64(const std::string& name, Poco::Int64 value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyString(const std::string& name, const std::string& value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyTimestamp(const std::string& name, Poco::Timestamp value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	std::vector < bool > toggle(std::vector < bool > flags);
		/// Sets flags by logically XOR-ing the currently set flags with
		/// the given ones.
		///
		/// Returns the previously set flags.

	virtual void toggleFlags(const std::vector < std::string >& flags);
		/// Sets flags by logically XOR-ing the currently set flags with
		/// the given ones.

	std::vector < bool > unset(std::vector < bool > flags);
		/// Unsets flags by logically AND-ing the currently set flags with
		/// the inverted given ones.
		///
		/// Returns the previously set flags.

	virtual void unsetFlags(const std::vector < std::string >& flags);
		/// Unsets flags by logically AND-ing the currently set flags with
		/// the inverted given ones.

	virtual bool valid() const;
		/// Returns true if a valid value is available.
		///
		/// Note that between the time valid() is called and
		/// a subsequent call to value() or similar method, the
		/// validity may change. Use validValue() or similar methods
		/// of subclasses to atomically get validity and value.

	Poco::Optional < std::vector < std::string > > validFlags() const;
		/// Returns a vector containing the symbolic names
		/// of all flags currently set if the datapoint is valid,
		/// otherwise an empty value.

	Poco::Optional < std::vector < bool > > validValue() const;
		/// Returns the bit vector value of the datapoint if
		/// it is valid, otherwise an empty value.

	std::vector < bool > value() const;
		/// Returns the bit vector value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

protected:
	void event__invalidated();

	void event__statusChanged(const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const std::vector < bool >& data);

	void event__valueChanged(const std::vector < bool >& data);

	void event__valueUpdated(const std::vector < bool >& data);

private:
	Poco::SharedPtr<IoT::Devices::FlagsDatapoint> _pServiceObject;
};


inline std::vector < IoT::Devices::FlagValue > FlagsDatapointRemoteObject::definedFlags() const
{
	return _pServiceObject->definedFlags();
}


inline std::vector < std::string > FlagsDatapointRemoteObject::flags() const
{
	return _pServiceObject->flags();
}


inline bool FlagsDatapointRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool FlagsDatapointRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double FlagsDatapointRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int FlagsDatapointRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline Poco::Int16 FlagsDatapointRemoteObject::getPropertyInt16(const std::string& name) const
{
	return _pServiceObject->getPropertyInt16(name);
}


inline Poco::Int64 FlagsDatapointRemoteObject::getPropertyInt64(const std::string& name) const
{
	return _pServiceObject->getPropertyInt64(name);
}


inline std::string FlagsDatapointRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline Poco::Timestamp FlagsDatapointRemoteObject::getPropertyTimestamp(const std::string& name) const
{
	return _pServiceObject->getPropertyTimestamp(name);
}


inline bool FlagsDatapointRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool FlagsDatapointRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline void FlagsDatapointRemoteObject::invalidate()
{
	_pServiceObject->invalidate();
}


inline const Poco::RemotingNG::Identifiable::TypeId& FlagsDatapointRemoteObject::remoting__typeId() const
{
	return IFlagsDatapoint::remoting__typeId();
}


inline std::vector < bool > FlagsDatapointRemoteObject::reset(std::vector < bool > value)
{
	return _pServiceObject->reset(value);
}


inline void FlagsDatapointRemoteObject::resetFlags(const std::vector < std::string >& flags)
{
	_pServiceObject->resetFlags(flags);
}


inline std::vector < bool > FlagsDatapointRemoteObject::set(std::vector < bool > flags)
{
	return _pServiceObject->set(flags);
}


inline void FlagsDatapointRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void FlagsDatapointRemoteObject::setFlags(const std::vector < std::string >& flags)
{
	_pServiceObject->setFlags(flags);
}


inline void FlagsDatapointRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void FlagsDatapointRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void FlagsDatapointRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void FlagsDatapointRemoteObject::setPropertyInt16(const std::string& name, Poco::Int16 value)
{
	_pServiceObject->setPropertyInt16(name, value);
}


inline void FlagsDatapointRemoteObject::setPropertyInt64(const std::string& name, Poco::Int64 value)
{
	_pServiceObject->setPropertyInt64(name, value);
}


inline void FlagsDatapointRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void FlagsDatapointRemoteObject::setPropertyTimestamp(const std::string& name, Poco::Timestamp value)
{
	_pServiceObject->setPropertyTimestamp(name, value);
}


inline std::vector < bool > FlagsDatapointRemoteObject::toggle(std::vector < bool > flags)
{
	return _pServiceObject->toggle(flags);
}


inline void FlagsDatapointRemoteObject::toggleFlags(const std::vector < std::string >& flags)
{
	_pServiceObject->toggleFlags(flags);
}


inline std::vector < bool > FlagsDatapointRemoteObject::unset(std::vector < bool > flags)
{
	return _pServiceObject->unset(flags);
}


inline void FlagsDatapointRemoteObject::unsetFlags(const std::vector < std::string >& flags)
{
	_pServiceObject->unsetFlags(flags);
}


inline bool FlagsDatapointRemoteObject::valid() const
{
	return _pServiceObject->valid();
}


inline Poco::Optional < std::vector < std::string > > FlagsDatapointRemoteObject::validFlags() const
{
	return _pServiceObject->validFlags();
}


inline Poco::Optional < std::vector < bool > > FlagsDatapointRemoteObject::validValue() const
{
	return _pServiceObject->validValue();
}


inline std::vector < bool > FlagsDatapointRemoteObject::value() const
{
	return _pServiceObject->value();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_FlagsDatapointRemoteObject_INCLUDED

