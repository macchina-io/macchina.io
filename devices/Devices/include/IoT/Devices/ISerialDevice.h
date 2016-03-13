//
// ISerialDevice.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ISerialDevice
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ISerialDevice_INCLUDED
#define IoT_Devices_ISerialDevice_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/SerialDevice.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ISerialDevice: public IoT::Devices::IDevice
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
	typedef Poco::AutoPtr<ISerialDevice> Ptr;

	ISerialDevice();
		/// Creates a ISerialDevice.

	virtual ~ISerialDevice();
		/// Destroys the ISerialDevice.

	virtual int available() const = 0;
		/// Returns the number of characters available from
		/// the internal buffer.

	virtual bool getRTS() const = 0;
		/// Returns the RTS status.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual bool poll(double timeout) = 0;
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in 
		/// the internal buffer, or if data arrives during the
		/// specified time interval (given in seconds), otherwise false.

	virtual Poco::UInt8 readByte() = 0;
		/// Reads a single character from the port.
		///
		/// If the internal buffer is empty, blocks until data
		/// arrives at the port.

	virtual std::string readLine(const std::string& delimiters, double timeout) = 0;
		/// Reads a characters from the serial port.
		///
		/// Characters will be read until one of the characters specified in delimiters
		/// is encountered, or no character is received for the specified timeout (in seconds).

	virtual std::string readString() = 0;
		/// Reads what's currently available from the serial port 
		/// or internal buffer and returns it in data.
		///
		/// If the internal buffer is empty, blocks until data
		/// arrives at the port.

	virtual void reconfigure(int baudRate, const std::string& parameters, const std::string& flowControl) = 0;
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

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setRTS(bool status) = 0;
		/// Manually sets or clears RTS.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void writeByte(Poco::UInt8 byte) = 0;
		/// Writes the given byte to the port.

	virtual void writeString(const std::string& data) = 0;
		/// Writes the given data to the port.
		/// Returns the number of characters written.

	Poco::BasicEvent < const std::string > lineReceived;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ISerialDevice_INCLUDED

