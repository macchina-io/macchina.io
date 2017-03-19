//
// SimPort.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  SimPort
//
// Definition of the SimPort class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_SimPort_INCLUDED
#define IoT_Modbus_SimPort_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/ModbusMaster.h"


namespace IoT {
namespace Modbus {


class IoTModbus_API SimPort
{
public:
	SimPort():
		_sent(false)
	{
	}

	~SimPort()
	{
	}

	template <class Message>
	void sendFrame(const Message& message)
	{
		_sent = message.functionCode == 0x03;
	}
	
	Poco::UInt8 receiveFrame(const Poco::Timespan& timeout)
	{
		return 0x03;
	}

	void decodeFrame(ReadHoldingRegistersResponse& message)
	{
		message.slaveOrUnitAddress = 0x12;
		message.functionCode = 0x03;
		message.registerValues.push_back(1);
		message.registerValues.push_back(2);
		message.registerValues.push_back(3);
		message.registerValues.push_back(4);
	}

	template <class Message>
	void decodeFrame(Message& message)
	{
	}
		
	bool poll(const Poco::Timespan& timeout)
	{
		Poco::Thread::sleep(100);
		if (_sent)
		{
			_sent = false;
			return true;
		}
		return false;
	}

	int maxSimultaneousTransactions() const
	{
		return 1;
	}

private:
	bool _sent;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_SimPort_INCLUDED
