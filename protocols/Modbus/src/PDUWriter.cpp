//
// PDUWriter.cpp
//
// Library: IoT/Modbus
// Package: ModbusCore
// Module:  PDUWriter
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x01
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Coils		2 Bytes	1 to 2000 (0x7D0)
	*/

	writeCommon(request);
	_writer << request.startingAddress << request.nOfCoils;
}


void PDUWriter::write(const ReadDiscreteInputsRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x02
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Inputs		2 Bytes	1 to 2000 (0x7D0)
	*/

	writeCommon(request);
	_writer << request.startingAddress << request.nOfInputs;
}


void PDUWriter::write(const ReadHoldingRegistersRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x03
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Registers	2 Bytes	1 to 127 (0x7D)
	*/

	writeCommon(request);
	_writer << request.startingAddress << request.nOfRegisters;
}


void PDUWriter::write(const ReadInputRegistersRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code				1 Byte	0x04
		Starting Address			2 Bytes	0x0000 to 0xFFFF
		Quantity of Input Registers	2 Bytes	0x0001 to 0x007D
	*/

	writeCommon(request);
	_writer << request.startingAddress << request.nOfRegisters;
}


void PDUWriter::write(const WriteSingleCoilRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x05
		Output Address			2 Bytes	0x0000 to 0xFFFF
		Output Value			2 Bytes 0x0000 or 0xFF00
	*/

	writeCommon(request);
	Poco::UInt16 outputValue = request.value ? 0xFF00 : 0x0000;
	_writer << request.outputAddress << outputValue;
}


void PDUWriter::write(const WriteSingleRegisterRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x06
		Register Address		2 Bytes	0x0000 to 0xFFFF
		Register Value			2 Bytes 0x0000 or 0xFFFF
	*/

	writeCommon(request);
	_writer << request.registerAddress << request.value;
}


void PDUWriter::write(const ReadExceptionStatusRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x07
	*/

	writeCommon(request);
}


void PDUWriter::write(const WriteMultipleCoilsRequest& request)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte		0x0F
		Starting Address		2 Bytes		0x0000 to 0xFFFF
		Quantity of Outputs		2 Bytes		0x0001 to 0x07B0
		Byte Count				1 Byte		N*
		Outputs Value			N* x 1 Byte value
		*N = Quantity of Outputs / 8, if the remainder is different of 0 => N = N+1
	*/

	writeCommon(request);
	_writer << request.startingAddress;
	Poco::UInt16 quantity = request.values.size();
	Poco::UInt8 byteCount = static_cast<Poco::UInt8>(quantity/8);
	if (quantity % 8 != 0 ) byteCount++;
	_writer << quantity;
	_writer << byteCount;
	Poco::UInt8 n = 0;
	while (n < byteCount && _writer.good())
	{
		Poco::UInt8 bits = 0;
		for (int i = 0; i < 8; i++)
		{
			Poco::UInt16 index = n*8 + i;
			if (index < quantity)
			{
				Poco::UInt8 bit = (request.values[index]) ? (1 << i) : 0;
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
		Function code			1 Byte			0x10
		Starting Address		2 Bytes			0x0000 to 0xFFFF
		Quantity of Registers	2 Bytes			0x0001 to 0x007B
		Byte Count				1 Byte			2 x N
		Registers Value			N* x 2 Bytes	value
		*N = Quantity of Registers
	*/

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
		Or_Mask				2 Bytes	0x0000 to 0xFFFF
	*/

	writeCommon(request);
	_writer << request.referenceAddress << request.andMask << request.orMask;
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
		Write Registers Value	N* x 2 Bytes
		*N = Quantity to Write
	*/

	writeCommon(request);
	_writer << request.readStartingAddress;
	_writer << request.readCount;
	_writer << request.writeStartingAddress;
	Poco::UInt16 quantity = request.values.size();
	_writer << quantity;
	_writer << static_cast<Poco::UInt8>(quantity*2);
	Poco::UInt16 n = 0;
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
		FIFO Pointer Address	2 Bytes	0x0000 to 0xFFFF
	*/

	writeCommon(request);
	_writer << request.fifoAddress;
}


void PDUWriter::write(const ModbusExceptionMessage& message)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	Function code + 0x80
		Exception code          1 Byte
	*/

	writeCommon(message);
	_writer << message.exceptionCode;
}


void PDUWriter::write(const ReadCoilsResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x01
		Byte count				1 Byte	N*
		Coil Status				n Byte	n = N or N+1
		*N = Quantity of Outputs / 8, if the remainder is different of 0 => N = N+1
	*/

	writeCommon(response);
	Poco::UInt16 quantity = response.coilStatus.size();
	Poco::UInt8 byteCount = static_cast<Poco::UInt8>(quantity/8);
	if (quantity % 8 != 0) byteCount++;
	_writer << byteCount;
	Poco::UInt8 n = 0;
	while (n < byteCount && _writer.good())
	{
		Poco::UInt8 bits = 0;
		for (int i = 0; i < 8; i++)
		{
			Poco::UInt16 index = n*8 + i;
			if (index < quantity)
			{
				Poco::UInt8 bit = (response.coilStatus[index]) ? (1 << i) : 0;
				bits |= bit;
			}
		}
		n++;
		_writer << bits;
	}
}


void PDUWriter::write(const ReadDiscreteInputsResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte		0x02
		Byte count				1 Byte		N*
		Coil Status				N* x 1 Byte
		*N = Quantity of Inputs / 8, if the remainder is different of 0 => N = N+1
	*/

	writeCommon(response);
	Poco::UInt16 quantity = response.inputStatus.size();
	Poco::UInt8 byteCount = static_cast<Poco::UInt8>(quantity/8);
	if (quantity % 8 != 0) byteCount++;
	_writer << byteCount;
	Poco::UInt8 n = 0;
	while (n < byteCount && _writer.good())
	{
		Poco::UInt8 bits = 0;
		for (int i = 0; i < 8; i++)
		{
			Poco::UInt16 index = n*8 + i;
			if (index < quantity)
			{
				Poco::UInt8 bit = response.inputStatus[index] ? (1 << i) : 0;
				bits |= bit;
			}
		}
		n++;
		_writer << bits;
	}
}


void PDUWriter::write(const ReadHoldingRegistersResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x03
		Byte count				1 Byte	2 x N*
		Register value			N* x 2 Bytes
		*N = Quantity of Registers
	*/

	writeCommon(response);
	Poco::UInt16 quantity = response.registerValues.size();
	_writer << static_cast<Poco::UInt8>(quantity*2);
	Poco::UInt16 n = 0;
	while (n < quantity && _writer.good())
	{
		_writer << response.registerValues[n];
		n++;
	}
}


void PDUWriter::write(const ReadInputRegistersResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x04
		Byte count				1 Byte	2 x N*
		Input Registers			N* x 2 Bytes
		*N = Quantity of Input Registers
	*/

	writeCommon(response);
	Poco::UInt16 quantity = response.registerValues.size();
	_writer << static_cast<Poco::UInt8>(quantity*2);
	Poco::UInt16 n = 0;
	while (n < quantity && _writer.good())
	{
		_writer << response.registerValues[n];
		n++;
	}
}


void PDUWriter::write(const WriteSingleCoilResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x05
		Output Address			2 Bytes	0x0000 to 0xFFFF
		Output Value			0x0000 or 0xFF00
	*/

	writeCommon(response);
	_writer << response.outputAddress << response.value;
}


void PDUWriter::write(const WriteSingleRegisterResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x06
		Register Address		2 Bytes	0x0000 to 0xFFFF
		Register Value			2 Bytes	0x0000 to 0xFFFF
	*/

	writeCommon(response);
	_writer << response.registerAddress << response.value;
}


void PDUWriter::write(const ReadExceptionStatusResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x07
		Output Data				1 Byte	0x00 to 0xFF
	*/

	writeCommon(response);
	_writer << response.data;
}


void PDUWriter::write(const WriteMultipleCoilsResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x0F
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Outputs		2 Bytes	0x0001 to 0x07B0
	*/

	writeCommon(response);
	_writer << response.startingAddress << response.nOfCoils;

}


void PDUWriter::write(const WriteMultipleRegistersResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x10
		Starting Address		2 Bytes	0x0000 to 0xFFFF
		Quantity of Registers	2 Bytes	1 to 123 (0x7B)
	*/

	writeCommon(response);
	_writer << response.startingAddress << response.nOfRegisters;
}


void PDUWriter::write(const MaskWriteRegisterResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte	0x16
		Reference Address		2 Bytes	0x0000 to 0xFFFF
		And_Mask				2 Bytes	0x0000 to 0xFFFF
		Or_Mask					2 Bytes	0x0000 to 0xFFFF
	*/

	writeCommon(response);
	_writer << response.referenceAddress << response.andMask << response.orMask;
}


void PDUWriter::write(const ReadWriteMultipleRegistersResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte			0x17
		Byte Count				1 Byte 			2 x N*
		Read Registers value	N'* x 2 Bytes
		*N' = Quantity to Read
	*/

	writeCommon(response);
	Poco::UInt16 quantity = response.values.size();
	_writer << static_cast<Poco::UInt8>(quantity*2);
	Poco::UInt16 n = 0;
	while (n < quantity && _writer.good())
	{
		_writer << response.values[n];
		n++;
	}
}


void PDUWriter::write(const ReadFIFOQueueResponse& response)
{
	/*	PDU data structure according to MODBUS specification
		Function code			1 Byte			0x18
		Byte Count				2 Bytes 			
		FIFO Count				2 Bytes			<= 31
		FIFO Value Register		N* x 2 Bytes
		*N = FIFO Count
	*/

	writeCommon(response);
	Poco::UInt16 fifoCount = response.values.size();
	_writer << static_cast<Poco::UInt8>(2 + fifoCount*2);
	_writer << fifoCount;
	Poco::UInt16 n = 0;
	while (n < fifoCount && _writer.good())
	{
		_writer << response.values[n];
		n++;
	}
}


void PDUWriter::writeCommon(const ModbusMessage& message)
{
	_writer << message.slaveOrUnitAddress << message.functionCode;
}


} } // namespace IoT::Modbus
