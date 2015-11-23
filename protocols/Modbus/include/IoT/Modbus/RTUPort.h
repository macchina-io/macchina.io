//
// RTUPort.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  RTUPort
//
// Definition of the RTUPort class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_RTUPort_INCLUDED
#define IoT_Modbus_RTUPort_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/PDUWriter.h"
#include "IoT/Modbus/PDUReader.h"
#include "IoT/Serial/SerialPort.h"
#include "Poco/Timespan.h"
#include "Poco/Buffer.h"
#include "Poco/SharedPtr.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"


namespace IoT {
namespace Modbus {


class IoTModbus_API RTUPort
	/// This class implements the Modbus RTU protocol over a serial line.
{
public:
	enum ByteOrder
		/// Byte order used by RTU protocol. 
		/// The Modbus specification required big endian.
	{
		RTU_BIG_ENDIAN = 1,
		RTU_LITTLE_ENDIAN = 2
	};
	
	RTUPort(Poco::SharedPtr<IoT::Serial::SerialPort> pSerialPort, Poco::Timespan interCharTimeout = 750, ByteOrder byteOrder = RTU_BIG_ENDIAN);
		/// Creates a RTUPort using the given SerialPort.
		///
		/// The recommended value for interCharTimeout is 750us.
		///
		/// The SerialPort must be open and properly configured
		/// for RS-485 communication with the Modbus slaves.
		
	~RTUPort();
		/// Destroys the RTUPort.

	template <class Message>
	void sendFrame(const Message& message)
		/// Sends a Modbus RTU frame over the wire.
	{
		Poco::MemoryOutputStream ostr(_sendBuffer.begin(), _sendBuffer.size());
		Poco::BinaryWriter binaryWriter(ostr, _byteOrder == RTU_BIG_ENDIAN ? Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER : Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
		PDUWriter pduWriter(binaryWriter);
		pduWriter.write(message);
		poco_assert (ostr.good());
		Poco::UInt16 crc = 0xffff;
		for (int i = 0; i < ostr.charsWritten(); i++)
		{
			crc = updateCRC16(crc, _sendBuffer[i]);
		}
		// CRC is sent in little endian (low-order byte, high-order byte)
		binaryWriter << static_cast<Poco::UInt8>(crc & 0xff);
		binaryWriter << static_cast<Poco::UInt8>((crc >> 8) & 0xff);
		poco_assert (ostr.good());
		_pSerialPort->write(_sendBuffer.begin(), ostr.charsWritten());
	}
	
	Poco::UInt8 receiveFrame();
		/// Receives the next frame from the wire. Returns the frame's function code.

	template <class Message>
	void receiveFrame(Message& message)
		/// Reads the currently buffered Modbus RTU frame.
		///
		/// The raw frame must have been read from the wire with receiveFrame().
	{
		Poco::MemoryInputStream istr(_receiveBuffer.begin(), _receiveBuffer.size());
		Poco::BinaryReader binaryReader(istr, _byteOrder == RTU_BIG_ENDIAN ? Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER : Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		PDUReader pduReader(binaryReader);
		pduReader.read(message);
		
	}
		
	bool poll(const Poco::Timespan& timeout);
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in 
		/// the internal buffer, or if data arrives during the
		/// specified time interval, otherwise false.

protected:
	Poco::UInt16 updateCRC16(Poco::UInt16 crc, Poco::UInt8 byte);
	bool checkFrame(std::size_t size);

private:
	enum
	{
		RTU_MAX_PDU_SIZE = 256
	};

	RTUPort();
	RTUPort(const RTUPort&);
	RTUPort& operator = (const RTUPort&);
	
	Poco::SharedPtr<IoT::Serial::SerialPort> _pSerialPort;
	Poco::Timespan _interCharTimeout;
	ByteOrder _byteOrder;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;
};


//
// inlines
//
inline bool RTUPort::poll(const Poco::Timespan& timeout)
{
	return _pSerialPort->poll(timeout);
}


} } // namespace IoT::XBee


#endif // IoT_XBee_XBeePort_INCLUDED
