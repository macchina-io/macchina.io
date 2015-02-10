//
// SensorEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SensorEventDispatcher_INCLUDED
#define IoT_Devices_SensorEventDispatcher_INCLUDED


#include "IoT/Devices/SensorRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class SensorEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
{
public:
	SensorEventDispatcher(SensorRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a SensorEventDispatcher.

	virtual ~SensorEventDispatcher();
		/// Destroys the SensorEventDispatcher.

	void event__valueChanged(const void* pSender, const double& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__valueChangedImpl(const std::string& subscriberURI, const double& data);

	static const std::string DEFAULT_NS;
	SensorRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SensorEventDispatcher::remoting__typeId() const
{
	return ISensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SensorEventDispatcher_INCLUDED

