//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "TCPPort.h"
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
	
	void createModbusTCPMaster(const std::string& uid, Poco::Net::SocketAddress& serverAddress, Poco::Timespan timeout)
	{		
		Poco::SharedPtr<ModbusMaster> pModbusMaster = new ModbusMasterImpl<TCPPort>(new TCPPort(serverAddress), timeout);
		std::string symbolicName = "io.macchina.modbus.tcp";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pModbusMasterRemoteObject = ServerHelper::createRemoteObject(pModbusMaster, oid);
		
		Properties props;
		props.set("io.macchina.protocol", symbolicName);
		props.set("io.macchina.modbus.tcp.device", serverAddress.toString());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pModbusMasterRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		
		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("modbus.tcp.ports", keys);
		int index = 0;
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "modbus.tcp.ports.";
			baseKey += *it;

			const std::string hostAddress = _pPrefs->configuration()->getString(baseKey + ".hostAddress", "");
			const Poco::UInt16 portNumber = _pPrefs->configuration()->getInt(baseKey + ".portNumber", 502);
			Poco::Net::SocketAddress serverAddress(hostAddress, portNumber);
			Poco::Timespan timeout = 1000*_pPrefs->configuration()->getInt(baseKey + ".timeout", 2000);
		
			try
			{
				pContext->logger().information(Poco::format("Use TCP port '%hu' on host '%s' for Modbus TCP device.", portNumber, hostAddress));							
				createModbusTCPMaster(Poco::NumberFormatter::format(index), serverAddress, timeout);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create TCP port for Modbus TCP device '%s': %s", serverAddress.toString(), exc.displayText())); 
			}
			index++;
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
