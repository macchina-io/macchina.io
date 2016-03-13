//
// SerialDeviceRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SerialDeviceRemoteObject_INCLUDED
#define IoT_Devices_SerialDeviceRemoteObject_INCLUDED


#include "IoT/Devices/ISerialDevice.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class SerialDeviceRemoteObject: public IoT::Devices::ISerialDevice, public Poco::RemotingNG::RemoteObject
	/// This class provides a simple interface for accessing
	/// a serial port.
	///
	/// There are two modes of operation for receiving data:
	/// polling (blocking) mode (default) and events (callback) mode.
	///
	/// In polling mode, repeatedly call poll() to detect
	/// if data is available, then call one of the read() methods
	/// to receive available data. The read() methods can also be
	/// called if no data is available, but will block until
	/// at least one character can be read.
	///
	/// In event mode the class will start a thread that polls
	/// and reads available data from the serial port, and fires
	/// the lineReceived event whenever something has been read.
	/// Since callback mode uses readLine() to receive entire lines
	/// (if possible), delimiter characters and timeout can be set
	/// via the "delimiters" (string) and "timeout" (double) properties.
	///
	/// Clients of the class can switch between polling and event
	/// mode by enabling or disabling the "events" feature:
	///
	///     setFeature("events", true);
{
public:
	typedef Poco::AutoPtr<SerialDeviceRemoteObject> Ptr;

	SerialDeviceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject);
		/// Creates a SerialDeviceRemoteObject.

	virtual ~SerialDeviceRemoteObject();
		/// Destroys the SerialDeviceRemoteObject.

	virtual int available() const;
		/// Returns the number of characters available from
		/// the internal buffer.

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

	virtual std::string getPropertyString(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual bool getRTS() const;
		/// Returns the RTS status.

	virtual bool hasFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.

	virtual bool hasProperty(const std::string& name) const;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.

	virtual bool poll(double timeout);
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in 
		/// the internal buffer, or if data arrives during the
		/// specified time interval (given in seconds), otherwise false.

	virtual Poco::UInt8 readByte();
		/// Reads a single character from the port.
		///
		/// If the internal buffer is empty, blocks until data
		/// arrives at the port.

	virtual std::string readLine(const std::string& delimiters, double timeout);
		/// Reads a characters from the serial port.
		///
		/// Characters will be read until one of the characters specified in delimiters
		/// is encountered, or no character is received for the specified timeout (in seconds).

	virtual std::string readString();
		/// Reads what's currently available from the serial port 
		/// or internal buffer and returns it in data.
		///
		/// If the internal buffer is empty, blocks until data
		/// arrives at the port.

	virtual void reconfigure(int baudRate, const std::string& parameters, const std::string& flowControl);
		/// Reconfigures the serial port with the given baud rate
		/// and communication parameters.
		///
		/// Baud rate must be one of the following:
		/// 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400,
		/// 4800, 9600, 19200, 38400, 57600, 115200 or 230400.
		///
		/// Specify -1 for baudRate to use the currently configured speed.
		/// Note that not all platforms support all baud rates.		
		///
		/// To specify character size, parity and stop bits, use the
		/// parameters argument. The parameters argument must be a three
		/// character string. The first character specifies the serial line
		/// character width in bits (5, 6, 7 or 8). The second char specifies
		/// the parity (N for none, E for even, O for odd) and the third
		/// character specifies the number of stop bits (1 or 2).
		/// Example: "8N1" for 8 bit characters, no parity, 1 stop bit.
		///
		/// To specify flow control, use the flowControl argument.
		/// Specify "none" or an empty string for no flow control.
		/// Specify "rtscts" for hardware (RTS/CTS) flow control.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setFeature(const std::string& name, bool enable);
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

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

	virtual void setPropertyString(const std::string& name, const std::string& value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setRTS(bool status);
		/// Manually sets or clears RTS.

	virtual void writeByte(Poco::UInt8 byte);
		/// Writes the given byte to the port.

	virtual void writeString(const std::string& data);
		/// Writes the given data to the port.
		/// Returns the number of characters written.

protected:
	void event__lineReceived(const std::string& data);

private:
	Poco::SharedPtr<IoT::Devices::SerialDevice> _pServiceObject;
};


inline int SerialDeviceRemoteObject::available() const
{
	return _pServiceObject->available();
}


inline bool SerialDeviceRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool SerialDeviceRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double SerialDeviceRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int SerialDeviceRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string SerialDeviceRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool SerialDeviceRemoteObject::getRTS() const
{
	return _pServiceObject->getRTS();
}


inline bool SerialDeviceRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool SerialDeviceRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline bool SerialDeviceRemoteObject::poll(double timeout)
{
	return _pServiceObject->poll(timeout);
}


inline Poco::UInt8 SerialDeviceRemoteObject::readByte()
{
	return _pServiceObject->readByte();
}


inline std::string SerialDeviceRemoteObject::readLine(const std::string& delimiters, double timeout)
{
	return _pServiceObject->readLine(delimiters, timeout);
}


inline std::string SerialDeviceRemoteObject::readString()
{
	return _pServiceObject->readString();
}


inline void SerialDeviceRemoteObject::reconfigure(int baudRate, const std::string& parameters, const std::string& flowControl)
{
	_pServiceObject->reconfigure(baudRate, parameters, flowControl);
}


inline const Poco::RemotingNG::Identifiable::TypeId& SerialDeviceRemoteObject::remoting__typeId() const
{
	return ISerialDevice::remoting__typeId();
}


inline void SerialDeviceRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void SerialDeviceRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void SerialDeviceRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void SerialDeviceRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void SerialDeviceRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void SerialDeviceRemoteObject::setRTS(bool status)
{
	_pServiceObject->setRTS(status);
}


inline void SerialDeviceRemoteObject::writeByte(Poco::UInt8 byte)
{
	_pServiceObject->writeByte(byte);
}


inline void SerialDeviceRemoteObject::writeString(const std::string& data)
{
	_pServiceObject->writeString(data);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SerialDeviceRemoteObject_INCLUDED

