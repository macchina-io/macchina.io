//
// SerialDevice.h
//
// $Id$
//
// Library: IoT/Devices
// Package: Devices
// Module:  SerialDevice
//
// Definition of the SerialDevice class.
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SerialDevice_INCLUDED
#define IoT_Devices_SerialDevice_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/AutoPtr.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API SerialDevice: public IoT::Devices::Device
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
	typedef Poco::AutoPtr<SerialDevice> Ptr;
	
	Poco::BasicEvent<const std::string> lineReceived;
		/// Fired when a line of text has been received on the serial port.

	SerialDevice();
		/// Creates the SerialDevice.
		
	~SerialDevice();
		/// Destroys the SerialDevice.
		
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
		
	virtual bool poll(double timeout) = 0;
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in 
		/// the internal buffer, or if data arrives during the
		/// specified time interval (given in seconds), otherwise false.

	virtual void setRTS(bool status) = 0;
		/// Manually sets or clears RTS.
		
	virtual bool getRTS() const = 0;
		/// Returns the RTS status.

	virtual void writeString(const std::string& data) = 0;
		/// Writes the given data to the port.
		/// Returns the number of characters written.

	virtual std::string readString() = 0;
		/// Reads what's currently available from the serial port 
		/// or internal buffer and returns it in data.
		///
		/// If the internal buffer is empty, blocks until data
		/// arrives at the port.
		
	virtual std::string readLine(const std::string& delimiters, double timeout) = 0;
		/// Reads a characters from the serial port.
		///
		/// Characters will be read until one of the characters specified in delimiters
		/// is encountered, or no character is received for the specified timeout (in seconds).

	virtual void writeByte(Poco::UInt8 byte) = 0;
		/// Writes the given byte to the port.

	virtual Poco::UInt8 readByte() = 0;
		/// Reads a single character from the port.
		///
		/// If the internal buffer is empty, blocks until data
		/// arrives at the port.

	virtual int available() const = 0;
		/// Returns the number of characters available from
		/// the internal buffer.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_SerialDevice_INCLUDED
