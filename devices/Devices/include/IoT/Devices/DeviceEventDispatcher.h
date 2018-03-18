//
// DeviceEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceEventDispatcher_INCLUDED
#define IoT_Devices_DeviceEventDispatcher_INCLUDED


#include "IoT/Devices/DeviceRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class DeviceEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for all devices and sensors.
	///
	/// This class defines a generic interface for setting
	/// and querying device properties and features.
	///
	/// The class also defines an event for notifications
	/// about changes to the device status.
	///
	/// Every implementation of Device should expose the
	/// following properties:
	///   - symbolicName: A name in reverse DNS notation that identifies the
	///     specific implementation of the device type.
	///   - type (string): A name in reverse DNS notation
	///     that identifies the generic device type (e.g., "io.macchina.serial").
	///   - name (string): A human-readable device type (e.g., "Serial Port").
	///   - status (int): Current device status (DeviceStatus); optional.
	///
	/// The following generic device types are currently defined:
	///   - io.macchina.accelerometer (Accelerometer)
	///   - io.macchina.barcode (BarcodeReader)
	///   - io.macchina.gnss (GNSSSensor)
	///   - io.macchina.gyroscope (Gyroscope)
	///   - io.macchina.io (IO)
	///   - io.macchina.led (LED)
	///   - io.macchina.magnetometer (Magnetometer)
	///   - io.macchina.rotary (RotaryEncoder)
	///   - io.macchina.sensor (Sensor)
	///   - io.macchina.boolean (BooleanSensor)
	///   - io.macchina.counter (Counter)
	///   - io.macchina.serial (SerialDevice)
	///   - io.macchina.switch (Switch)
	///   - io.macchina.trigger (Trigger)
{
public:
	DeviceEventDispatcher(DeviceRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a DeviceEventDispatcher.

	virtual ~DeviceEventDispatcher();
		/// Destroys the DeviceEventDispatcher.

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	DeviceRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceEventDispatcher::remoting__typeId() const
{
	return IDevice::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DeviceEventDispatcher_INCLUDED

