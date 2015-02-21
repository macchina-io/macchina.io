//
// Device.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Device.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Device
//
// Definition of the Device interface.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Device_INCLUDED
#define IoT_Devices_Device_INCLUDED


#include "IoT/Devices/Devices.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Device
	/// The base class for all devices and sensors.
	///
	/// This class defines a generic interface for setting
	/// and querying device properties and features.
	///
	/// Every implementation of Device should expose the
	/// following properties:
	///   - symbolicName (string): A name in reverse DNS notation
	///     that identifies the device type (e.g., "io.macchina.serialport").
	///   - name (string): A human-readable device type (e.g., "Serial Port").
{
public:
	Device();
		/// Creates the Device.
		
	virtual ~Device();
		/// Destroys the Device.

	virtual void setPropertyString(const std::string& name, const std::string& value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.
		
	virtual std::string getPropertyString(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual void setPropertyInt(const std::string& name, int value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.
		
	virtual int getPropertyInt(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual void setPropertyDouble(const std::string& name, double value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.
		
	virtual double getPropertyDouble(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual void setPropertyBool(const std::string& name, bool value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.
		
	virtual bool getPropertyBool(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.
	
	virtual bool hasProperty(const std::string& name) const = 0;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.
		
	virtual void setFeature(const std::string& name, bool enable) = 0;
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.
	
	virtual bool getFeature(const std::string& name) const = 0;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.
	
	virtual bool hasFeature(const std::string& name) const = 0;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Device_INCLUDED
