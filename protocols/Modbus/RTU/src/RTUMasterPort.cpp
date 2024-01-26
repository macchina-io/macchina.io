//
// RTUMasterPort.cpp
//
// Library: IoT/Modbus/RTU
// Package: RTU
// Module:  RTUMasterPort
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/RTU/RTUMasterPort.h"


namespace IoT {
namespace Modbus {
namespace RTU {


RTUMasterPort::RTUMasterPort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort, Poco::Timespan frameTimeout, ByteOrder byteOrder):
	_pSerialPort(pSerialPort),
	_frameTimeout(frameTimeout),
	_byteOrder(byteOrder),
	_sendBuffer(RTU_MAX_PDU_SIZE),
	_receiveBuffer(RTU_MAX_PDU_SIZE)
{
}


RTUMasterPort::~RTUMasterPort()
{
}


Poco::UInt8 RTUMasterPort::receiveFrame()
{
	std::size_t n = 0;
	bool frameComplete = false;
	do
	{
		std::size_t rd = _pSerialPort->read(_receiveBuffer.begin() + n, _receiveBuffer.size() - n, _frameTimeout);
		if (rd == 0) return 0;
		if (rd == 1 && n == 0 && _receiveBuffer[0] == 0)
		{
			// ignore spurious null bytes before frame
			if (poll(_frameTimeout))
				continue;
			else
				throw Poco::TimeoutException();
		}
		n += rd;
		frameComplete = checkFrame(n);
	}
	while (!frameComplete && n < _receiveBuffer.size());

	return frameComplete ? _receiveBuffer[1] : 0;
}


void RTUMasterPort::reset()
{
	_pSerialPort->drain();
	Poco::Timespan timeout(_frameTimeout);
	while (_pSerialPort->available() > 0 || _pSerialPort->poll(timeout))
	{
		std::string buffer;
		_pSerialPort->read(buffer);
	}
}


bool RTUMasterPort::checkFrame(std::size_t size)
{
	poco_assert (size <= _receiveBuffer.size());

	if (size < 4) return false;

	Poco::MemoryInputStream istr(_receiveBuffer.begin(), size);
	Poco::BinaryReader binaryReader(istr, _byteOrder == RTU_BIG_ENDIAN ? Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER : Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);

	CRC16 crc;
	for (int i = 0; i < size - 2; i++)
	{
		Poco::UInt8 byte;
		binaryReader >> byte;
		crc.update(byte);
	}
	Poco::UInt8 loCRC, hiCRC;
	binaryReader >> loCRC >> hiCRC;
	Poco::UInt16 receivedCRC = loCRC + (hiCRC << 8);
	return crc.checksum() == receivedCRC;
}


} } } // namespace IoT::Modbus::RTU
