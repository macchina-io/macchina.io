//
// IModbusMaster.cpp
//
// Library: IoT/Modbus
// Package: Generated
// Module:  IModbusMaster
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Modbus/IModbusMaster.h"


namespace IoT {
namespace Modbus {


IModbusMaster::IModbusMaster():
	Poco::OSP::Service(),
	badFrameReceived(),
	exceptionReceived(),
	maskWriteRegisterResponseReceived(),
	readCoilsResponseReceived(),
	readDiscreteInputsResponseReceived(),
	readExceptionStatusResponseReceived(),
	readFIFOQueueResponseReceived(),
	readHoldingRegistersResponseReceived(),
	readInputRegistersResponseReceived(),
	readWriteMultipleRegistersResponseReceived(),
	responseReceived(),
	timeout(),
	writeMultipleCoilsResponseReceived(),
	writeMultipleRegistersResponseReceived(),
	writeSingleCoilResponseReceived(),
	writeSingleRegisterResponseReceived()
{
}


IModbusMaster::~IModbusMaster()
{
}


bool IModbusMaster::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IModbusMaster::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Modbus.ModbusMaster");
	return REMOTING__TYPE_ID;
}


const std::type_info& IModbusMaster::type() const
{
	return typeid(IModbusMaster);
}


} // namespace Modbus
} // namespace IoT

