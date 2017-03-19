//
// PDUReader.cpp
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  PDUReader
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Modbus/PDUReader.h"


namespace IoT {
namespace Modbus {


PDUReader::PDUReader(Poco::BinaryReader& reader):
	_reader(reader)
{
}


PDUReader::~PDUReader()
{
}


void PDUReader::read(GenericMessage& message)
{
	readCommon(message);
	while (_reader.good())
	{
		Poco::UInt8 byte;
		_reader >> byte;
		if (!_reader.eof())
		{
			message.data.push_back(byte);
		}
	}
}


void PDUReader::read(ModbusExceptionMessage& message)
{
	readCommon(message);
	_reader >> message.exceptionCode;
}


void PDUReader::read(ReadCoilsResponse& response)
{
	readCommon(response);
	Poco::UInt8 n;
	_reader >> n;
	response.coilStatus.clear();
	while (n-- > 0 && _reader.good())
	{
		Poco::UInt8 bits;
		_reader >> bits;
		for (int i = 0; i < 8; i++)
		{
			Poco::UInt8 bit = bits & 0x01;
			response.coilStatus.push_back(bit);
			bits >>= 1;
		}
		_reader >> bits;
	}
}


void PDUReader::read(ReadDiscreteInputsResponse& response)
{
	readCommon(response);
	Poco::UInt8 n;
	_reader >> n;
	response.inputStatus.clear();
	while (n-- > 0 && _reader.good())
	{
		Poco::UInt8 bits;
		_reader >> bits;
		for (int i = 0; i < 8; i++)
		{
			Poco::UInt8 bit = bits & 0x01;
			response.inputStatus.push_back(bit);
			bits >>= 1;
		}
		_reader >> bits;
	}
}


void PDUReader::read(ReadHoldingRegistersResponse& response)
{
	readCommon(response);
	Poco::UInt8 n;
	_reader >> n;
	response.registerValues.clear();
	n /= 2;
	while (n-- > 0 && _reader.good())
	{
		Poco::UInt16 value;
		_reader >> value;
		response.registerValues.push_back(value);
	}
}


void PDUReader::read(ReadInputRegistersResponse& response)
{
	readCommon(response);
	Poco::UInt8 n;
	_reader >> n;
	response.registerValues.clear();
	n /= 2;
	while (n-- > 0 && _reader.good())
	{
		Poco::UInt16 value;
		_reader >> value;
		response.registerValues.push_back(value);
	}
}


void PDUReader::read(WriteSingleCoilResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x05
		Output Address			2 Bytes	0x0000 to 0xFFFF
		Output Value			2 Bytes	0x0000 or 0xFF00*/

	readCommon(response);
	Poco::UInt16 value;
	_reader >> value;
	response.value = (0xFF00 == value)?true:false;
}


void PDUReader::read(WriteSingleRegisterResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte		0x06
		Register Address		2 Bytes		0x0000 to 0xFFFF
		Register Value			2 Bytes		0x0000 or 0xFF00*/

	readCommon(response);
	_reader >> response.value;
}


void PDUReader::read(ReadExceptionStatusResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte		0x07
		Output Data				1 Byte		0x00 to 0xFF*/

	readCommon(response);
	_reader >> response.data;
}


void PDUReader::read(WriteMultipleCoilsResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x0F
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Outputs		2 Bytes	0x0001 to 0x07B0*/

	readCommon(response);
	_reader >> response.startingAddress;
	_reader >> response.nOfCoils;
}


void PDUReader::read(WriteMultipleRegistersResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte		0x10
		Starting Address		2 Bytes		0x0000 to 0xFFFF
		Quantity of Registers	2 Bytes		1 to 123 (0x7B)*/

	readCommon(response);
	_reader >> response.startingAddress;
	_reader >> response.nOfRegisters;
}


void PDUReader::read(MaskWriteRegisterResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x16
		Reference Address		2 Bytes	0x0000 to 0xFFFF
		And_Mask				2 Bytes	0x0000 to 0xFFFF
		Or_Mask					2 Bytes	0x0000 to 0xFFFF*/

	readCommon(response);
	response.referenceAddress = response.slaveOrUnitAddress;
	_reader >> response.andMask;
	_reader >> response.orMask;
}


void PDUReader::read(ReadWriteMultipleRegistersResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x17
		Byte Count				1 Byte	2 x N'
		Read Registers value	N' x 2 Bytes
		N' = Quantity to Read*/

	readCommon(response);
	Poco::UInt8 n;
	_reader >> n;
	response.values.clear();
	n /= 2;
	while (n-- > 0 && _reader.good())
	{
		Poco::UInt16 value;
		_reader >> value;
		response.values.push_back(value);
	}
}


void PDUReader::read(ReadFIFOQueueResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte		0x18
		Byte Count				2 Bytes
		FIFO Count				2 Bytes		<=31
		FIFO Value Register		FIFO Count x 2 Bytes*/

	readCommon(response);
	Poco::UInt16 byteCount;
	Poco::UInt16 fifoCount;
	_reader >> byteCount;
	_reader >> fifoCount;
	response.values.clear();
	while (fifoCount-- > 0 && _reader.good())
	{
		Poco::UInt16 value;
		_reader >> value;
		response.values.push_back(value);
	}
}


void PDUReader::readCommon(ModbusMessage& message)
{
	_reader >> message.slaveOrUnitAddress >> message.functionCode;
}


} } // namespace IoT::Modbus
