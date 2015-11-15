//
// PDUReader.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  PDUReader
//
// Definition of the PDUReader class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_PDUReader_INCLUDED
#define IoT_Modbus_PDUReader_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/ModbusMaster.h"
#include "Poco/BinaryReader.h"


namespace IoT {
namespace Modbus {


class IoTModbus_API PDUReader
	/// The PDUReader class is used to write Modbus PDU data
	/// using a Poco::BinaryWriter.
{
public:
	PDUReader(Poco::BinaryReader& reader);
		/// Creates the PDUReader using the given Poco::BinaryReader.
		
	~PDUReader();
		/// Destroys the PDUReader.
	
	void read(GenericMessage& message);
	void read(ModbusExceptionMessage& message);
	void read(ReadCoilsResponse& response);
	void read(ReadDiscreteInputsResponse& response);
	void read(ReadHoldingRegistersResponse& response);
	void read(ReadInputRegistersResponse& response);
	void read(WriteSingleCoilResponse& response);
	void read(WriteSingleRegisterResponse& response);
	void read(ReadExceptionStatusResponse& response);
	void read(WriteMultipleCoilsResponse& response);
	void read(WriteMultipleRegistersResponse& response);
	void read(MaskWriteRegisterResponse& response);
	void read(ReadWriteMultipleRegistersResponse& response);
	void read(ReadFIFOQueueResponse& response);
	
protected:
	void readCommon(ModbusMessage& message);

private:
	PDUReader();
	PDUReader(const PDUReader&);
	PDUReader& operator = (const PDUReader&);

	Poco::BinaryReader& _reader;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_PDUReader_INCLUDED
