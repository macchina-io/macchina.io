//
// TCPPort.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  TCPPort
//
// Definition of the TCPPort class.
//
// Copyright (c) 2015-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_TCPPort_INCLUDED
#define IoT_Modbus_TCPPort_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/PDUWriter.h"
#include "IoT/Modbus/PDUReader.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Timespan.h"
#include "Poco/Timestamp.h"
#include "Poco/Buffer.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"


namespace IoT {
namespace Modbus {
namespace TCP {


class TCPPort
	/// This class implements the Modbus TCP protocol over a socket.
{
public:
	TCPPort(const Poco::Net::SocketAddress& serverAddress, Poco::Timespan frameTimeout = 10000);
		/// Creates a TCPPort using the given server address.
		
	~TCPPort();
		/// Destroys the TCPPort.

	template <class Message>
	void sendFrame(const Message& message)
		/// Sends a Modbus RTU frame over the wire.
	{
		// We write the PDU before the MBAP header (which comes first in the frame)
		// since we need to know the size.
		
		// PDU
		Poco::MemoryOutputStream pduStream(_sendBuffer.begin() + MBAP_HEADER_SIZE, _sendBuffer.size());
		Poco::BinaryWriter binaryWriter(pduStream, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
		PDUWriter pduWriter(binaryWriter);
		pduWriter.write(message);
		
		// MBAP header
		Poco::MemoryOutputStream mbapStream(_sendBuffer.begin(), MBAP_HEADER_SIZE);
		Poco::BinaryWriter mbapWriter(mbapStream, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
		mbapWriter << message.transactionID;
		mbapWriter << static_cast<Poco::UInt16>(0); // protocol ID, always 0
		mbapWriter << static_cast<Poco::UInt16>(ostr.charsWritten());
		
		_socket.sendBytes(_sendBuffer.begin(), ostr.charsWritten() + MBAP_HEADER_SIZE);
	}
	
	Poco::UInt8 receiveFrame(const Poco::Timespan& timeout);
		/// Receives the next frame from the wire. Returns the frame's function code.

	template <class Message>
	void decodeFrame(Message& message)
		/// Decodes the currently buffered Modbus TCP frame.
		///
		/// The raw frame must have been read from the wire with receiveFrame().
	{
		Poco::MemoryInputStream istr(_receiveBuffer.begin(), _receiveBuffer.size());
		Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
		
		// MBAP header
		Poco::UInt16 protocolID;
		Poco::UInt16 length;
		binaryReader >> message.transactionID >> protocolID >> length;
		if (protocolID != 0) throw Poco::ProtocolException("invalid Modbus TCP Protocol Identifier");
		if (length == 0) throw Poco::ProtocolException("invalid Modbus TCP frame length");
		
		PDUReader pduReader(binaryReader);
		pduReader.read(message);
	}
		
	bool poll(const Poco::Timespan& timeout);
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in 
		/// the internal buffer, or if data arrives during the
		/// specified time interval, otherwise false.

	int maxSimultaneousTransactions() const;
		/// Returns the maximum number of simultaneous transactions allowed by
		/// the port.

private:
	enum
	{
		MBAP_HEADER_SIZE = 6,
		MAX_PDU_SIZE = 256
	};

	TCPPort();
	TCPPort(const TCPPort&);
	TCPPort& operator = (const TCPPort&);
	
	Poco::Net::SocketAddress _serverAddress;
	Poco::Net::StreamSocket _socket;
	Poco::Timespan _frameTimeout;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;
};


//
// inlines
//
inline bool TCPPort::poll(const Poco::Timespan& timeout)
{
	return _socket->poll(timeout, Poco::Net::Socket::SELECT_READ);
}


inline int TCPPort::maxSimultaneousTransactions() const
{
	return 16;
}


} } } // namespace IoT::Modbus::TCP


#endif // IoT_Modbus_TCPPort_INCLUDED
