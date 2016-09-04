//
// XBeePort.h
//
// $Id$
//
// Library: IoT/XBee
// Package: XBee
// Module:  XBeePort
//
// Definition of the XBeePort class.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeePort_INCLUDED
#define IoT_XBee_XBeePort_INCLUDED


#include "IoT/XBee/XBee.h"
#include "Poco/Serial/SerialPort.h"
#include "Poco/Timespan.h"
#include "Poco/Buffer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XBee {


class XBeeFrame;


class IoTXBee_API XBeePort
	/// This class provides an interface to a Digi XBee module
	/// using the Digi XBee API frame-based protocol.
{
public:
	XBeePort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort);
		/// Creates a XBeePort using the given SerialPort.
		///
		/// The SerialPort must be open and properly configured
		/// for communication with the Digi XBee module.
		
	~XBeePort();
		/// Destroys the ZBPort.

	void sendFrame(const XBeeFrame& frame);
		/// Sends an API frame to the XBee ZB module.

	std::size_t receiveFrame(XBeeFrame& frame);
		/// Receives an API frame from the XBee ZB module.
		///
		/// Blocks until data becomes available.
		
	std::size_t receiveFrame(XBeeFrame& frame, const Poco::Timespan& timeout);
		/// Receives an API frame from the XBee ZB module.
		///
		/// Returns the number of bytes received, which may be 0 if the
		/// receive operation times out.

	bool poll(const Poco::Timespan& timeout);
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in 
		/// the internal buffer, or if data arrives during the
		/// specified time interval, otherwise false.

private:
	XBeePort();
	XBeePort(const XBeePort&);
	XBeePort& operator = (const XBeePort&);
	
	Poco::SharedPtr<Poco::Serial::SerialPort> _pSerialPort;
	Poco::Buffer<char> _buffer;
};


//
// inlines
//
inline bool XBeePort::poll(const Poco::Timespan& timeout)
{
	return _pSerialPort->poll(timeout);
}


} } // namespace IoT::XBee


#endif // IoT_XBee_XBeePort_INCLUDED
