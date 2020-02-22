//
// BooleanSensorEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanSensorEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BooleanSensorEventDispatcher_INCLUDED
#define IoT_Devices_BooleanSensorEventDispatcher_INCLUDED


#include "IoT/Devices/BooleanSensorRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class BooleanSensorEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for two-state sensors measuring
	/// on/off or open/closed state.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanSensor implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	BooleanSensorEventDispatcher(BooleanSensorRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a BooleanSensorEventDispatcher.

	virtual ~BooleanSensorEventDispatcher();
		/// Destroys the BooleanSensorEventDispatcher.

	void event__stateChanged(const void* pSender, const bool& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const bool& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	BooleanSensorRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BooleanSensorEventDispatcher::remoting__typeId() const
{
	return IBooleanSensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BooleanSensorEventDispatcher_INCLUDED

