//
// ModbusMasterCreator.h
//
// Library: IoT/Modbus
// Package: ModbusMasterCreator
// Module:  ModbusMasterCreator
//
// Definition of the ModbusMasterCreator class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_ModbusMasterCreator_INCLUDED
#define IoT_Modbus_ModbusMasterCreator_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/ModbusMaster.h"
#include "Poco/Timespan.h"
#include "Poco/SharedPtr.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRef.h"
#include <vector>


namespace IoT {
namespace Modbus {


class IoTModbus_API ModbusMasterCreator
	/// This class wraps funstions for RTU and TCP Modbus master cration.
{
public:
	static Poco::SharedPtr<ModbusMaster> createRTU(const std::string& uid,
		const std::string& device,
		const std::string& params = "8N1",
		int speed = 9600,
		bool rtsOnSend = false,
		bool rtsAfterSend = false,
		bool useGPIO = false,
		int delayRTSBeforeSend = 0,
		int delayRTSAfterSend = 0,
		int gpioPin = 0,
		Poco::Timespan timeout = 2000,
		Poco::Timespan frameTimeout = 10000);
			/// Creates Modbus RTU master.

	static Poco::OSP::ServiceRef::Ptr createRTU(Poco::OSP::BundleContext::Ptr pContext,
	const std::string& uid,
		const std::string& device,
		const std::string& params = "8N1",
		int speed = 9600,
		bool rtsOnSend = false,
		bool rtsAfterSend = false,
		bool useGPIO = false,
		int delayRTSBeforeSend = 0,
		int delayRTSAfterSend = 0,
		int gpioPin = 0,
		Poco::Timespan timeout = 2000,
		Poco::Timespan frameTimeout = 10000);
			/// Creates Modbus RTU master and registers it as a service.

	static Poco::SharedPtr<ModbusMaster> createTCP(const std::string& uid, const std::string& hostAndPort, Poco::Timespan timeout = 10000);
			/// Creates Modbus TCP master.

	static Poco::OSP::ServiceRef::Ptr createTCP(Poco::OSP::BundleContext::Ptr pContext,
		const std::string& uid,
		const std::string& hostAndPort,
		Poco::Timespan timeout = 10000);
			/// Creates Modbus TCP master and registers it as a service.

private:
	ModbusMasterCreator(const ModbusMasterCreator&);
	ModbusMasterCreator& operator = (const ModbusMasterCreator&);
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusMasterCreator_INCLUDED
