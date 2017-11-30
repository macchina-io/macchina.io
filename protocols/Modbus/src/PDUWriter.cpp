//
// PDUWriter.cpp
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  PDUWriter
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Modbus/PDUWriter.h"


namespace IoT {
namespace Modbus {


PDUWriter::PDUWriter(Poco::BinaryWriter& writer):
	_writer(writer)
{
}


PDUWriter::~PDUWriter()
{
}


void PDUWriter::write(const GenericMessage& message)
{
	writeCommon(message);
	for (std::vector<Poco::UInt8>::const_iterator it = message.data.begin(); it != message.data.end(); ++it)
	{
		_writer << *it;
	}
}


void PDUWriter::write(const ReadCoilsRequest& request)
{
	writeCommon(request);
	_writer << request.startingAddress << request.nOfCoils;
}


void PDUWriter::write(const ReadDiscreteInputsRequest& request)
{
	writeCommon(request);
	_writer << request.startingAddress << request.nOfInputs;
}


void PDUWriter::write(const ReadHoldingRegistersRequest& request)
{
	writeCommon(request);
	_writer << request.startingAddress << request.nOfRegisters;
}


void PDUWriter::write(const ReadInputRegistersRequest& request)
{
	writeCommon(request);
	_writer << request.startingAddress << request.nOfRegisters;
}


void PDUWriter::write(const WriteSingleCoilRequest& request)
{
	writeCommon(request);
	Poco::UInt16 outputValue = request.value ? 0xFF00 : 0x0000;
	_writer << request.outputAddress << outputValue;
}


void PDUWriter::write(const WriteSingleRegisterRequest& request)
{
	writeCommon(request);
	_writer << request.outputAddress << request.value;
}


void PDUWriter::write(const ReadExceptionStatusRequest& request)
{
	writeCommon(request);
}


void PDUWriter::write(const WriteMultipleCoilsRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x0F
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Outputs		2 Bytes	0x0001 to 0x07B0
		Byte Count				1 Byte	N*
		Outputs Value			N* x 1 Byte value
		N* = Quantity of Outputs / 8, if the remainder is different of 0 =>N = N+1*/
	writeCommon(request);
	_writer << request.startingAddress;
	Poco::UInt16 quantity = request.values.size();
	Poco::UInt8 nBytes = quantity/8;
	if (quantity%8 != 0 )
		nBytes++;

	_writer << quantity;
	_writer << nBytes;

	Poco::UInt8 n = 0;
	Poco::UInt8 index = 0;
	while (n < nBytes && _writer.good())
	{
		Poco::UInt8 bits = 0;
		for (int i = 0; i < 8; i++)
		{
			index = n*8 + i;
			if (index < quantity)
			{
				Poco::UInt8 bit = (request.values[index])?1<<i:0;
				bits |= bit;
			}
		}
		n++;
		_writer << bits;
	}
}


void PDUWriter::write(const WriteMultipleRegistersRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x10
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Registers	2 Bytes	0x0001 to 0x007B
		Byte Count				1 Byte	2 x N
		Registers Value			N x 2 Bytes value
		N = Quantity of Registers*/

	writeCommon(request);
	_writer << request.startingAddress;
	Poco::UInt16 quantity = request.values.size();
	Poco::UInt8 byteCount = static_cast<Poco::UInt8>(quantity*2);
	_writer << quantity << byteCount;
	Poco::UInt8 n = 0;
	while (n < quantity && _writer.good())
	{
		_writer << request.values[n];
		n++;
	}
}


void PDUWriter::write(const MaskWriteRegisterRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code		1 Byte	0x16
		Reference Address	2 Bytes	0x0000 to 0xFFFF
		And_Mask			2 Bytes	0x0000 to 0xFFFF
		Or_Mask				2 Bytes	0x0000 to 0xFFFF*/

	writeCommon(request);
	_writer << request.referenceAddress;
	_writer << request.andMask;
	_writer << request.orMask;
}


void PDUWriter::write(const ReadWriteMultipleRegistersRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x17
		Read Starting Address	2 Bytes	0x0000 to 0xFFFF
		Quantity to Read		2 Bytes	0x0001 to 0x007D
		Write Starting Address	2 Bytes	0x0000 to 0xFFFF
		Quantity to Write		2 Bytes	0x0001 to 0X0079
		Write Byte Count		1 Byte	2 x N
		Write Registers Value	N x 2 Bytes
		N = Quantity to Write*/

	writeCommon(request);
	_writer << request.readStartingAddress;
	_writer << request.readCount;
	_writer << request.writeStartingAddress;
	Poco::UInt8 quantity = request.values.size();
	_writer << static_cast<Poco::UInt16>(quantity);
	_writer << static_cast<Poco::UInt8>(quantity*2);
	Poco::UInt8 n = 0;
	while (n < quantity && _writer.good())
	{
		_writer << request.values[n];
		n++;
	}
}


void PDUWriter::write(const ReadFIFOQueueRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x18
		FIFO Pointer Address	2 Bytes	0x0000 to 0xFFFF*/
	writeCommon(request);
	_writer << request.fifoAddress;
}


void PDUWriter::writeCommon(const ModbusMessage& message)
{
	_writer << message.slaveOrUnitAddress << message.functionCode;
}


} } // namespace IoT::Modbus
