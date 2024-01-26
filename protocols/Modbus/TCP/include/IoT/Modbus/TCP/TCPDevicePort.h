//
// TCPDevicePort.h
//
// Library: IoT/Modbus/TCP
// Package: TCP
// Module:  TCPDevicePort
//
// Definition of the TCPDevicePort class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_TCP_TCPDevicePort_INCLUDED
#define IoT_Modbus_TCP_TCPDevicePort_INCLUDED


#include "IoT/Modbus/TCP/ModbusTCP.h"
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
#include <atomic>


namespace IoT {
namespace Modbus {
namespace TCP {


class IoTModbusTCP_API TCPDevicePort
	/// This class implements the Modbus TCP protocol over a socket.
{
public:
	TCPDevicePort(const Poco::Net::StreamSocket& socket);
		/// Creates a TCPDevicePort using the given socket.

	~TCPDevicePort();
		/// Destroys the TCPDevicePort.
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

		try
		{
			int n = _socket.sendBytes(_sendBuffer.begin(), pduStream.charsWritten() + MBAP_HEADER_SIZE);
			poco_assert (n >= 0);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error(Poco::format("Error sending frame through TCP socket: %s", exc.displayText()));
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

	Poco::UInt8 frameSlaveOrUnitAddress() const
		/// Returns the slave or unit address of the most recent
		/// frame received by receiveFrame(). 
	{
		return _receiveBuffer[MBAP_HEADER_SIZE];
	}

	bool poll(const Poco::Timespan& timeout);
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in
		/// the internal buffer, or if data arrives during the
		/// specified timeout interval, otherwise false.

	bool isConnected() const;
		/// Returns true if the socket is connected, otherwise false.

	std::string address() const;
		/// Returns the client address.

private:
	enum
	{
		MBAP_HEADER_SIZE = 6,
		PROTOCOL_ID = 0,
		MAX_PDU_SIZE = 256
	};

	TCPDevicePort();
	TCPDevicePort(const TCPDevicePort&);
	TCPDevicePort& operator = (const TCPDevicePort&);

	void disconnect();
	int receiveBytes(char* buffer, int length);

	Poco::Net::StreamSocket _socket;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;
	std::atomic<bool> _isConnected{true};
	Poco::Logger& _logger;
};


//
// inlines
//
inline bool TCPDevicePort::poll(const Poco::Timespan& timeout)
{
	return _socket.poll(timeout, Poco::Net::Socket::SELECT_READ);
}


inline bool TCPDevicePort::isConnected() const
{
	return _isConnected;
}


inline std::string TCPDevicePort::address() const
{
	return _socket.peerAddress().toString();
}


} } } // namespace IoT::Modbus::TCP


#endif // IoT_Modbus_TCP_TCPDevicePort_INCLUDED
