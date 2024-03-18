//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "IoT/Modbus/TCP/TCPMasterPort.h"
#include "IoT/Modbus/ModbusMasterImpl.h"
#include "IoT/Modbus/ModbusMasterServerHelper.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;
using namespace std::string_literals;


namespace IoT {
namespace Modbus {
namespace TCP {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::Modbus::ModbusMaster> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createModbusTCPMaster(const std::string& uid, const Poco::Net::SocketAddress& serverAddress, Poco::Timespan timeout, Poco::Timespan connectTimeout, bool connectImmediately, std::size_t maxSimultaneousTransactions, std::size_t maxAsyncQueueSize)
	{
		Poco::SharedPtr<ModbusMaster> pModbusMaster = new ModbusMasterImpl<TCPMasterPort>(new TCPMasterPort(serverAddress, connectTimeout, connectImmediately, maxSimultaneousTransactions), timeout, maxAsyncQueueSize);
		std::string symbolicName = "io.macchina.modbus.tcp"s;
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pModbusMasterRemoteObject = ServerHelper::createRemoteObject(pModbusMaster, oid);

		Properties props;
		props.set("io.macchina.protocol"s, symbolicName);
		props.set("io.macchina.modbus.tcp.device"s, serverAddress.toString());

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pModbusMasterRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("modbus.tcp.ports"s, keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "modbus.tcp.ports."s;
			baseKey += *it;
			if (_pPrefs->configuration()->getBool(baseKey + ".enable", true))
            {
				const std::string hostAddress = _pPrefs->configuration()->getString(baseKey + ".hostAddress"s, ""s);
				const Poco::UInt16 portNumber = _pPrefs->configuration()->getInt(baseKey + ".portNumber"s, 502);
				const Poco::Net::SocketAddress serverAddress(hostAddress, portNumber);
				const int timeoutMS = _pPrefs->configuration()->getInt(baseKey + ".timeout"s, 2000);
				const Poco::Timespan timeout = Poco::Timespan::MILLISECONDS*timeoutMS;
				const int connectTimeoutMS = _pPrefs->configuration()->getInt(baseKey + ".connectTimeout"s, timeoutMS);
				const Poco::Timespan connectTimeout = Poco::Timespan::MILLISECONDS*connectTimeoutMS;
				const bool connectImmediately = !_pPrefs->configuration()->getBool(baseKey + ".lazyConnect"s, false);
				const std::size_t maxSimultaneousTransactions = _pPrefs->configuration()->getUInt16(baseKey + ".maxSimultaneousTransactions"s, 16);
				const std::size_t maxAsyncQueueSize = _pPrefs->configuration()->getUInt32(baseKey + ".maxAsyncQueueSize"s, 256);

				try
				{
					pContext->logger().information(Poco::format("Use TCP port '%hu' on host '%s' for Modbus TCP device."s, portNumber, hostAddress));
					createModbusTCPMaster(*it, serverAddress, timeout, connectTimeout, connectImmediately, maxSimultaneousTransactions, maxAsyncQueueSize);
				}
				catch (Poco::Exception& exc)
				{
					pContext->logger().error(Poco::format("Cannot create TCP port for Modbus TCP device '%s': %s"s, serverAddress.toString(), exc.displayText()));
				}
			}
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();
		_pPrefs = 0;
		_pContext = 0;

		ServerHelper::shutdown();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::Modbus::TCP


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Modbus::TCP::BundleActivator)
POCO_END_MANIFEST
