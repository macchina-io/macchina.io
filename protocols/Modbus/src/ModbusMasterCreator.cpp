//
// ModbusMasterCreator.cpp
//
// Library: IoT/Modbus
// Package: ModbusMasterCreator
// Module:  ModbusMasterCreator
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/ModbusMasterCreator.h"


#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "RTUPort.h"
#include "TCPPort.h"
#include "IoT/Modbus/ModbusMasterImpl.h"
#include "IoT/Modbus/ModbusMasterServerHelper.h"
#include "Poco/Serial/SerialPort.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace Modbus {


using Poco::Serial::SerialPort;


typedef Poco::RemotingNG::ServerHelper<IoT::Modbus::ModbusMaster> ServerHelper;


Poco::SharedPtr<ModbusMaster> ModbusMasterCreator::createRTU(const std::string& uid,
	const std::string& device,
	const std::string& params,
	int speed,
	bool rtsOnSend,
	bool rtsAfterSend,
	bool useGPIO,
	int delayRTSBeforeSend,
	int delayRTSAfterSend,
	int gpioPin,
	Poco::Timespan timeout,
	Poco::Timespan frameTimeout)
{
	Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort = new Poco::Serial::SerialPort(device, speed, params);

	Poco::Serial::SerialPort::RS485Params rs485Params;
	rs485Params.flags = Poco::Serial::SerialPort::RS485Params::RS485_ENABLED;
	if (rtsOnSend)
		rs485Params.flags |= Poco::Serial::SerialPort::RS485Params::RS485_RTS_ON_SEND;
	if (rtsAfterSend)
		rs485Params.flags |= Poco::Serial::SerialPort::RS485Params::RS485_RTS_AFTER_SEND;
	if (useGPIO)
		rs485Params.flags |= Poco::Serial::SerialPort::RS485Params::RS485_USE_GPIO;

	rs485Params.delayRTSBeforeSend = delayRTSBeforeSend;
	rs485Params.delayRTSAfterSend  = delayRTSAfterSend;
	rs485Params.gpioPin            = gpioPin;

	pSerialPort->configureRS485(rs485Params);
	return new ModbusMasterImpl<RTU::RTUPort>(new RTU::RTUPort(pSerialPort, frameTimeout), timeout);
}


ServiceRef::Ptr ModbusMasterCreator::createRTU(BundleContext::Ptr pContext,
	const std::string& uid,
	const std::string& device,
	const std::string& params,
	int speed,
	bool rtsOnSend,
	bool rtsAfterSend,
	bool useGPIO,
	int delayRTSBeforeSend,
	int delayRTSAfterSend,
	int gpioPin,
	Poco::Timespan timeout,
	Poco::Timespan frameTimeout)
{
	Poco::SharedPtr<ModbusMaster> pModbusMaster = createRTU(uid, device, params, speed, rtsOnSend,
		rtsAfterSend, useGPIO, delayRTSBeforeSend, delayRTSAfterSend, gpioPin, timeout, frameTimeout);

	std::string symbolicName = "io.macchina.modbus.rtu";
	Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
	oid += '#';
	oid += uid;
	ServerHelper::RemoteObjectPtr pModbusMasterRemoteObject = ServerHelper::createRemoteObject(pModbusMaster, oid);
	Properties props;
	props.set("io.macchina.protocol", symbolicName);
	props.set("io.macchina.modbus.rtu.device", device);
	return pContext->registry().registerService(oid, pModbusMasterRemoteObject, props);
}


Poco::SharedPtr<ModbusMaster> ModbusMasterCreator::createTCP(const std::string& uid, const std::string& hostAndPort, Poco::Timespan timeout)
{
	Poco::Net::SocketAddress serverAddress(hostAndPort);
	return new ModbusMasterImpl<TCP::TCPPort>(new TCP::TCPPort(serverAddress), timeout);
}


ServiceRef::Ptr ModbusMasterCreator::createTCP(BundleContext::Ptr pContext, const std::string& uid, const std::string& hostAndPort, Poco::Timespan timeout)
{
	Poco::SharedPtr<ModbusMaster> pModbusMaster = createTCP(uid, hostAndPort, timeout);
	std::string symbolicName = "io.macchina.modbus.tcp";
	Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
	oid += '#';
	oid += uid;
	ServerHelper::RemoteObjectPtr pModbusMasterRemoteObject = ServerHelper::createRemoteObject(pModbusMaster, oid);
	Properties props;
	props.set("io.macchina.protocol", symbolicName);
	props.set("io.macchina.modbus.tcp.device", hostAndPort);
	return pContext->registry().registerService(oid, pModbusMasterRemoteObject, props);
}


} } // namespace IoT::Modbus
