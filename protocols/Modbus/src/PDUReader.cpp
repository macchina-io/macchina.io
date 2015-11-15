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
		message.data.push_back(byte);
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
	readCommon(response);
	// TODO
}


void PDUReader::read(WriteSingleRegisterResponse& response)
{
	readCommon(response);
	// TODO
}


void PDUReader::read(ReadExceptionStatusResponse& response)
{
	readCommon(response);
	// TODO
}


void PDUReader::read(WriteMultipleCoilsResponse& response)
{
	readCommon(response);
	// TODO
}


void PDUReader::read(WriteMultipleRegistersResponse& response)
{
	readCommon(response);
}


void PDUReader::read(MaskWriteRegisterResponse& response)
{
	readCommon(response);
}


void PDUReader::read(ReadWriteMultipleRegistersResponse& response)
{
	readCommon(response);
}


void PDUReader::read(ReadFIFOQueueResponse& response)
{
	readCommon(response);
}


void PDUReader::readCommon(ModbusMessage& message)
{
	_reader >> message.slaveOrUnitAddress >> message.functionCode;
}


} } // namespace IoT::Modbus
