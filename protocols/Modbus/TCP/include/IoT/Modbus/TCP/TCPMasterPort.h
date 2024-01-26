//
// TCPMasterPort.h
//
// Library: IoT/Modbus/TCP
// Package: TCP
// Module:  TCPMasterPort
//
// Definition of the TCPMasterPort class.
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_TCP_TCPMasterPort_INCLUDED
#define IoT_Modbus_TCP_TCPMasterPort_INCLUDED


#include "IoT/Modbus/TCP/ModbusTCP.h"
#include "IoT/Modbus/PDUWriter.h"
#include "IoT/Modbus/PDUReader.h"
#include "IoT/Modbus/Types.h"
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


class IoTModbusTCP_API TCPMasterPort
	/// This class implements the Modbus TCP protocol over a socket.
{
public:
	Poco::BasicEvent<const ConnectionState> connectionStateChanged;

	TCPMasterPort(const Poco::Net::SocketAddress& serverAddress, Poco::Timespan connectTimeout, bool connectImmediately = true);
		/// Creates a TCPMasterPort using the given server address.
		///
		/// Try connect to underlying socket in constructor.
		/// If connect failed the TCPMasterPort class try reconnect at the begin
		/// of every sendFrame() and receiveFrame() function
		/// to reconnect. If this also fail an IOException is thrown.

	~TCPMasterPort();
		/// Destroys the TCPMasterPort.
		///
		/// Try to close the underlying socket.

	template <class Message>
	void sendFrame(const Message& message)
		/// Sends a Modbus TCP frame over the wire.
		///
		/// Throws an IOException if the port is not connected.
	{
		reconnectIfRequired();

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

		try
		{
			int n = _socket.sendBytes(_sendBuffer.begin(), pduStream.charsWritten() + MBAP_HEADER_SIZE);
			poco_assert (n >= 0);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error(Poco::format("Error sending frame through TCP socket: %s", exc.displayText()));
			changeConnectionState(CONNECTION_ERROR);
			disconnect();
		}
	}

	Poco::UInt8 receiveFrame();
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
		/// specified timeout interval, otherwise false.

	int maxSimultaneousTransactions() const;
		/// Returns the maximum number of simultaneous transactions allowed by
		/// the port.

	void reset();
		/// Closes and re-opens the connection.

	std::string address() const;
		/// Returns the server address.

protected:
	void changeConnectionState(ConnectionState state)
	{
		if (state != _state)
		{
			_state = state;
			connectionStateChanged(this, state);
		}
	}

private:
	enum
	{
		MBAP_HEADER_SIZE = 6,
		PROTOCOL_ID = 0,
		MAX_PDU_SIZE = 256,
		MAX_SIMULTANEOUS_TRANSACTIONS = 16
	};

	TCPMasterPort();
	TCPMasterPort(const TCPMasterPort&);
	TCPMasterPort& operator = (const TCPMasterPort&);

	void connect();
	void disconnect(const bool active = true);
	void reconnectIfRequired();
	int receiveBytes(void* buffer, int length);

	Poco::Net::SocketAddress _serverAddress;
	Poco::Timespan _connectTimeout;
	Poco::Net::StreamSocket _socket;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;
	ConnectionState _state;
	Poco::Logger& _logger;
};


//
// inlines
//
inline bool TCPMasterPort::poll(const Poco::Timespan& timeout)
{
	if (_state == CONNECTION_OPEN && _socket.impl()->initialized())
	{
		return _socket.poll(timeout, Poco::Net::Socket::SELECT_READ);
	}
	else return false;
}


inline int TCPMasterPort::maxSimultaneousTransactions() const
{
	return MAX_SIMULTANEOUS_TRANSACTIONS;
}


inline std::string TCPMasterPort::address() const
{
	return _serverAddress.toString();
}


} } } // namespace IoT::Modbus::TCP


#endif // IoT_Modbus_TCP_TCPMasterPort_INCLUDED
