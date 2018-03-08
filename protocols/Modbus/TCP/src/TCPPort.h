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
#include "Poco/Logger.h"
#include "Poco/MemoryStream.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Modbus {
namespace TCP {


class TCPPort
	/// This class implements the Modbus TCP protocol over a socket.
{
public:
	Poco::BasicEvent<void> connectionEstablished;
		/// Fired after the handshake to the port is complete and the
		/// connection has been established.

	Poco::BasicEvent<void> connectionClosing;	
		/// Fired when the connection to the port is about to be closed.
		
	Poco::BasicEvent<void> connectionClosed;	
		/// Fired after the connection to the port has been closed.

	TCPPort(const Poco::Net::SocketAddress& serverAddress);
		/// Creates a TCPPort using the given server address.
		/// 
		/// Try connect to underlying socket in constructor.
		/// If connect failed the TCPPort class try reconnect at the begin
		/// of every sendFrame() and receiveFrame() function
		/// to reconnect. If this also fail an IOException is thrown.
		
	~TCPPort();
		/// Destroys the TCPPort.
		///
		/// Try to close the underlying socket.

	template <class Message>
	void sendFrame(const Message& message)
		/// Sends a Modbus TCP frame over the wire.
		///
		/// Throws an IOException if the port is not connected.
	{
		// We write the PDU before the MBAP header (which comes first in the frame)
		// since we need to know the size.
		
		// PDU
		Poco::MemoryOutputStream pduStream(_sendBuffer.begin() + MBAP_HEADER_SIZE, _sendBuffer.size());
		Poco::BinaryWriter binaryWriter(pduStream, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
		PDUWriter pduWriter(binaryWriter);
		pduWriter.write(message);

		poco_assert (pduStream.good());
		
		// MBAP header
		Poco::MemoryOutputStream mbapStream(_sendBuffer.begin(), MBAP_HEADER_SIZE);
		Poco::BinaryWriter mbapWriter(mbapStream, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
		mbapWriter << message.transactionID;
		mbapWriter << static_cast<Poco::UInt16>(PROTOCOL_ID); // protocol ID, always 0
		mbapWriter << static_cast<Poco::UInt16>(pduStream.charsWritten());

		poco_assert (mbapStream.good());

		poco_assert (mbapStream.charsWritten() == MBAP_HEADER_SIZE);

		reconnectIfRequired();
		
		try
		{
			int n = _socket.sendBytes(_sendBuffer.begin(), pduStream.charsWritten() + MBAP_HEADER_SIZE);
			poco_assert(n >= 0);
		}
		catch (Poco::Exception& exc)
		{
			_logger.fatal(Poco::format("Error sending frame to TCP socket: %s", exc.displayText()));
			disconnect();
		}
	}
	
	Poco::UInt8 receiveFrame(const Poco::Timespan& timeout);
		/// Receives the next frame from the wire. Returns the frame's function code.
		///
		/// Throws an IOException if the port is not connected.

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
		if (protocolID != PROTOCOL_ID) throw Poco::ProtocolException("invalid Modbus TCP Protocol Identifier"); // protocol ID, always 0
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
		PROTOCOL_ID = 0,
		MAX_PDU_SIZE = 256
	};

	enum ConnectionState
	{
		STATE_ESTABLISHED,
			/// The connection is ready.

		STATE_CLOSED
			/// The connection has been closed.
	};

	TCPPort();
	TCPPort(const TCPPort&);
	TCPPort& operator = (const TCPPort&);

	void connect();
	void disconnect(const bool active = true);

	void reconnectIfRequired();

	int receiveBytes(void* buffer, int length);
	
	Poco::Net::SocketAddress _serverAddress;
	Poco::Net::StreamSocket _socket;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;

	ConnectionState _state;
	Poco::Logger& _logger;
};


//
// inlines
//
inline bool TCPPort::poll(const Poco::Timespan& timeout)
{
	return _socket.poll(timeout, Poco::Net::Socket::SELECT_READ);
}


inline int TCPPort::maxSimultaneousTransactions() const
{
	return 16;
}


} } } // namespace IoT::Modbus::TCP


#endif // IoT_Modbus_TCPPort_INCLUDED
