//
// PDUWriter.h
//
// Library: IoT/Modbus
// Package: ModbusCore
// Module:  PDUWriter
//
// Definition of the PDUWriter class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_PDUWriter_INCLUDED
#define IoT_Modbus_PDUWriter_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/ModbusMaster.h"
#include "Poco/BinaryWriter.h"


namespace IoT {
namespace Modbus {


class IoTModbus_API PDUWriter
	/// The PDUWriter class is used to write Modbus PDU data
	/// using a Poco::BinaryWriter.
{
public:
	PDUWriter(Poco::BinaryWriter& writer);
		/// Creates the PDUWriter using the given Poco::BinaryWriter.
		
	~PDUWriter();
		/// Destroys the PDUWriter.
	
	void write(const GenericMessage& message);
	void write(const ReadCoilsRequest& request);
	void write(const ReadDiscreteInputsRequest& request);
	void write(const ReadHoldingRegistersRequest& request);
	void write(const ReadInputRegistersRequest& request);
	void write(const WriteSingleCoilRequest& request);
	void write(const WriteSingleRegisterRequest& request);
	void write(const ReadExceptionStatusRequest& request);
	void write(const WriteMultipleCoilsRequest& request);
	void write(const WriteMultipleRegistersRequest& request);
	void write(const MaskWriteRegisterRequest& request);
	void write(const ReadWriteMultipleRegistersRequest& request);
	void write(const ReadFIFOQueueRequest& request);
	void write(const ModbusExceptionMessage& message);
	void write(const ReadCoilsResponse& response);
	void write(const ReadDiscreteInputsResponse& response);
	void write(const ReadHoldingRegistersResponse& response);
	void write(const ReadInputRegistersResponse& response);
	void write(const WriteSingleCoilResponse& response);
	void write(const WriteSingleRegisterResponse& response);
	void write(const ReadExceptionStatusResponse& response);
	void write(const WriteMultipleCoilsResponse& response);
	void write(const WriteMultipleRegistersResponse& response);
	void write(const MaskWriteRegisterResponse& response);
	void write(const ReadWriteMultipleRegistersResponse& response);
	void write(const ReadFIFOQueueResponse& response);

protected:
	void writeCommon(const ModbusMessage& message);

private:
	PDUWriter();
	PDUWriter(const PDUWriter&);
	PDUWriter& operator = (const PDUWriter&);

	Poco::BinaryWriter& _writer;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_PDUWriter_INCLUDED
