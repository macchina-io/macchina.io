//
// PDUWriter.cpp
//
// $Id$
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
	writeCommon(request);
	// TODO
}


void PDUWriter::write(const WriteMultipleRegistersRequest& request)
{
	writeCommon(request);
	// TODO
}


void PDUWriter::write(const MaskWriteRegisterRequest& request)
{
	writeCommon(request);
	// TODO
}


void PDUWriter::write(const ReadWriteMultipleRegistersRequest& request)
{
	writeCommon(request);
	// TODO
}


void PDUWriter::write(const ReadFIFOQueueRequest& request)
{
	writeCommon(request);
	// TODO
}


void PDUWriter::writeCommon(const ModbusMessage& message)
{
	_writer << message.slaveOrUnitAddress << message.functionCode;
}


} } // namespace IoT::Modbus
