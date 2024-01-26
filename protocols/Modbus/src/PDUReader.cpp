//
// PDUReader.cpp
//
// Library: IoT/Modbus
// Package: ModbusCore
// Module:  PDUReader
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
	while (_reader.stream().peek() != std::char_traits<char>::eof())
	{
		Poco::UInt8 byte;
		_reader >> byte;
		message.data.push_back(byte);
	}
}


void PDUReader::read(ReadCoilsRequest& request)
{
	readCommon(request);
	_reader >> request.startingAddress >> request.nOfCoils;
}


void PDUReader::read(ReadDiscreteInputsRequest& request)
{
	readCommon(request);
	_reader >> request.startingAddress >> request.nOfInputs;
}


void PDUReader::read(ReadHoldingRegistersRequest& request)
{
	readCommon(request);
	_reader >> request.startingAddress >> request.nOfRegisters;
}


void PDUReader::read(ReadInputRegistersRequest& request)
{
	readCommon(request);
	_reader >> request.startingAddress >> request.nOfRegisters;
}


void PDUReader::read(WriteSingleCoilRequest& request)
{
	readCommon(request);
	Poco::UInt16 outputValue;
	_reader >> request.outputAddress >> outputValue;
	request.value = outputValue != 0;
}


void PDUReader::read(WriteSingleRegisterRequest& request)
{
	readCommon(request);
	_reader >> request.registerAddress >> request.value;
}


void PDUReader::read(ReadExceptionStatusRequest& request)
{
	readCommon(request);
}


void PDUReader::read(WriteMultipleCoilsRequest& request)
{
	readCommon(request);
	Poco::UInt16 quantity;
	Poco::UInt8 byteCount;
	_reader >> request.startingAddress >> quantity >> byteCount;
	Poco::UInt8 byte;
	request.values.clear();
	request.values.reserve(quantity);
	for (Poco::UInt16 index = 0; index < quantity; index++)
	{
		Poco::UInt16 bit = index % 8;
		if (bit == 0)
		{
			_reader >> byte;
		}
		request.values.push_back(((byte >> bit) & 0x01) != 0);
	}
}


void PDUReader::read(WriteMultipleRegistersRequest& request)
{
	readCommon(request);
	Poco::UInt16 quantity;
	Poco::UInt8 byteCount;
	_reader >> request.startingAddress >> quantity >> byteCount;
	request.values.clear();
	request.values.reserve(quantity);
	for (Poco::UInt16 index = 0; index < quantity; index++)
	{
		Poco::UInt16 value;
		_reader >> value;
		request.values.push_back(value);
	}
}


void PDUReader::read(MaskWriteRegisterRequest& request)
{
	readCommon(request);
	_reader >> request.referenceAddress >> request.andMask >> request.orMask;
}


void PDUReader::read(ReadWriteMultipleRegistersRequest& request)
{
	readCommon(request);
	_reader >> request.readStartingAddress >> request.readCount >> request.writeStartingAddress;
	Poco::UInt16 quantity;
	Poco::UInt8 byteCount;
	_reader >> quantity >> byteCount;
	request.values.clear();
	request.values.reserve(quantity);
	for (Poco::UInt16 index = 0; index < quantity; index++)
	{
		Poco::UInt16 value;
		_reader >> value;
		request.values.push_back(value);
	}
}


void PDUReader::read(ReadFIFOQueueRequest& request)
{
	readCommon(request);
	_reader >> request.fifoAddress;
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
	readCommon(response);
	Poco::UInt16 value;
	_reader >> response.outputAddress;
	_reader >> value;
	response.value = (0xFF00 == value)?true:false;
}


void PDUReader::read(WriteSingleRegisterResponse& response)
{
	readCommon(response);
	_reader >> response.registerAddress;
	_reader >> response.value;
}


void PDUReader::read(ReadExceptionStatusResponse& response)
{
	readCommon(response);
	_reader >> response.data;
}


void PDUReader::read(WriteMultipleCoilsResponse& response)
{
	readCommon(response);
	_reader >> response.startingAddress;
	_reader >> response.nOfCoils;
}


void PDUReader::read(WriteMultipleRegistersResponse& response)
{
	readCommon(response);
	_reader >> response.startingAddress;
	_reader >> response.nOfRegisters;
}


void PDUReader::read(MaskWriteRegisterResponse& response)
{
	readCommon(response);
	_reader >> response.referenceAddress;
	_reader >> response.andMask;
	_reader >> response.orMask;
}


void PDUReader::read(ReadWriteMultipleRegistersResponse& response)
{
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
