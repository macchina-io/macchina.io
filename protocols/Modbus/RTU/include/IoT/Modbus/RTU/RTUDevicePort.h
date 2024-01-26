//
// RTUDevicePort.h
//
// Library: IoT/Modbus/RTU
// Package: RTU
// Module:  RTUDevicePort
//
// Definition of the RTUDevicePort class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_RTU_RTU_RTUDevicePort_INCLUDED
#define IoT_Modbus_RTU_RTU_RTUDevicePort_INCLUDED


#include "IoT/Modbus/RTU/ModbusRTU.h"
#include "IoT/Modbus/RTU/CRC16.h"
#include "IoT/Modbus/PDUWriter.h"
#include "IoT/Modbus/PDUReader.h"
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


class IoTModbusRTU_API RTUDevicePort
	/// This class implements the Modbus RTU protocol over a serial line.
{
public:
	RTUDevicePort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort, Poco::Timespan frameTimeout = 10000);
		/// Creates a RTUDevicePort using the given SerialPort.
		///
		/// The recommended value for frameTimeout is 10ms.
		///
		/// The SerialPort must be open and properly configured
		/// for RS-485 communication with the Modbus slaves.

	~RTUDevicePort();
		/// Destroys the RTUDevicePort.

	template <class Message>
	void sendFrame(const Message& message)
		/// Sends a Modbus RTU frame over the wire.
	{
		Poco::MemoryOutputStream ostr(_sendBuffer.begin(), _sendBuffer.size());
		Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
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
		Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
		PDUReader pduReader(binaryReader);
		pduReader.read(message);
	}

	Poco::UInt8 frameSlaveOrUnitAddress() const
		/// Returns the slave or unit address of the most recent
		/// frame received by receiveFrame(). 
	{
		return _receiveBuffer[0];
	}

	bool poll(const Poco::Timespan& timeout);
		/// Waits for data to arrive at the port.
		///
		/// Returns true immediately if data is already in
		/// the internal buffer, or if data arrives during the
		/// specified time interval, otherwise false.

	bool isConnected() const;
		/// Always returns true.

	std::string address() const;
		/// Returns the client device name.

protected:
	bool checkFrame(std::size_t size);

private:
	enum
	{
		RTU_MAX_PDU_SIZE = 256
	};

	RTUDevicePort();
	RTUDevicePort(const RTUDevicePort&);
	RTUDevicePort& operator = (const RTUDevicePort&);

	Poco::SharedPtr<Poco::Serial::SerialPort> _pSerialPort;
	Poco::Timespan _frameTimeout;
	Poco::Buffer<char> _sendBuffer;
	Poco::Buffer<char> _receiveBuffer;
};


//
// inlines
//
inline bool RTUDevicePort::poll(const Poco::Timespan& timeout)
{
	return _pSerialPort->poll(timeout);
}


inline bool RTUDevicePort::isConnected() const
{
	return true;
}


inline std::string RTUDevicePort::address() const
{
    return _pSerialPort->device();
}


} } } // namespace IoT::Modbus::RTU


#endif // IoT_Modbus_RTU_RTU_RTUDevicePort_INCLUDED
