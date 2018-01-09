//
// NPIPort.h
//
// Definition of the NPIPort class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CISS_NPIPort_INCLUDED
#define IoT_CISS_NPIPort_INCLUDED


#include "Poco/Serial/SerialPort.h"
#include "Poco/Timespan.h"
#include "Poco/Buffer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CISS {


class NPIFrame;


class NPIPort
	/// This class provides an interface to a CISS node
	/// over USB using the NPI protocol.
{
public:
	typedef Poco::SharedPtr<NPIPort> Ptr;

	NPIPort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort);
		/// Creates a NPIPort using the given SerialPort.
		///
		/// The SerialPort must be open and properly configured
		/// for communication with the CISS node.

	~NPIPort();
		/// Destroys the NPIPort.

	void sendFrame(const NPIFrame& frame);
		/// Sends a NPI frame to the CISS module.

	std::size_t receiveFrame(NPIFrame& frame, const Poco::Timespan& timeout);
		/// Receives an API frame from the CISS module.
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
	NPIPort();
	NPIPort(const NPIPort&);
	NPIPort& operator = (const NPIPort&);

	Poco::SharedPtr<Poco::Serial::SerialPort> _pSerialPort;
	Poco::Buffer<char> _buffer;
};


//
// inlines
//
inline bool NPIPort::poll(const Poco::Timespan& timeout)
{
	return _pSerialPort->poll(timeout);
}


} } // namespace IoT::CISS


#endif // IoT_CISS_NPIPort_INCLUDED
