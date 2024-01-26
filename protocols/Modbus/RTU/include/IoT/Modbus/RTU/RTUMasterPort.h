//
// RTUMasterPort.h
//
// Library: IoT/Modbus/RTU
// Package: RTU
// Module:  RTUMasterPort
//
// Definition of the RTUMasterPort class.
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_RTU_RTUMasterPort_INCLUDED
#define IoT_Modbus_RTU_RTUMasterPort_INCLUDED


#include "IoT/Modbus/RTU/ModbusRTU.h"
#include "IoT/Modbus/RTU/CRC16.h"
#include "IoT/Modbus/PDUWriter.h"
#include "IoT/Modbus/PDUReader.h"
#include "IoT/Modbus/Types.h"
#include "Poco/Serial/SerialPort.h"
#include "Poco/Timespan.h"
#include "Poco/Timestamp.h"
#include "Poco/Buffer.h"
#include "Poco/SharedPtr.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"


namespace IoT {
namespace Modbus {
namespace RTU {


class IoTModbusRTU_API RTUMasterPort
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

	Poco::BasicEvent<const ConnectionState> connectionStateChanged;
		/// Required by MasterPort interface, but not used for RTU.

	RTUMasterPort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort, Poco::Timespan frameTimeout = 10000, ByteOrder byteOrder = RTU_BIG_ENDIAN);
		/// Creates a RTUMasterPort using the given SerialPort.
		///
		/// The recommended value for frameTimeout is 10ms.
		///
		/// The SerialPort must be open and properly configured
		/// for RS-485 communication with the Modbus slaves.

	~RTUMasterPort();
		/// Destroys the RTUMasterPort.

	template <class Message>
	void sendFrame(const Message& message)
		/// Sends a Modbus RTU frame over the wire.
	{
		Poco::MemoryOutputStream ostr(_sendBuffer.begin(), _sendBuffer.size());
		Poco::BinaryWriter binaryWriter(ostr, _byteOrder == RTU_BIG_ENDIAN ? Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER : Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
		PDUWriter pduWriter(binaryWriter);
		pduWriter.write(message);
		poco_assert (ostr.good());
		CRC16 crc;
		for (int i = 0; i < ostr.charsWritten(); i++)
		{
			crc.update(_sendBuffer[i]);
		}
		// CRC is sent in little endian (low-order byte, high-order byte)
		binaryWriter << static_cast<Poco::UInt8>(crc.checksum() & 0xff);
		binaryWriter << static_cast<Poco::UInt8>((crc.checksum() >> 8) & 0xff);
		poco_assert (ostr.good());
		_pSerialPort->write(_sendBuffer.begin(), ostr.charsWritten());
	}

	Poco::UInt8 receiveFrame();
		/// Receives the next frame from the wire. Returns the frame's function code.

	template <class Message>
	void decodeFrame(Message& message)
		/// Decodes the currently buffered Modbus RTU frame.
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

	int maxSimultaneousTransactions() const;
		/// Returns the maximum number of simultaneous transactions allowed by
		/// the port.

	void reset();
		/// Resets the connection to the bus.

	std::string address() const;
		/// Returns the device name.

protected:
	bool checkFrame(std::size_t size);

private:
	enum
	{
		RTU_MAX_PDU_SIZE = 256
	};

	RTUMasterPort();
	RTUMasterPort(const RTUMasterPort&);
	RTUMasterPort& operator = (const RTUMasterPort&);

	Poco::SharedPtr<Poco::Serial::SerialPort> _pSerialPort;
	Poco::Timespan _frameTimeout;
	ByteOrder _byteOrder;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;
};


//
// inlines
//
inline bool RTUMasterPort::poll(const Poco::Timespan& timeout)
{
	return _pSerialPort->poll(timeout);
}


inline int RTUMasterPort::maxSimultaneousTransactions() const
{
	return 1;
}


inline std::string RTUMasterPort::address() const
{
    return _pSerialPort->device();
}


} } } // namespace IoT::Modbus::RTU


#endif // IoT_Modbus_RTU_RTUMasterPort_INCLUDED
