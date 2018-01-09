//
// BundleActivator.cpp
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceImpl.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceServerHelper.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;


namespace IoT {
namespace NetworkEnvironment {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::NetworkEnvironment::NetworkEnvironmentService> ServerHelper;

	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		NetworkEnvironmentServiceImpl::Ptr pNetworkEnvironmentService = new NetworkEnvironmentServiceImpl;
		std::string oid("io.macchina.services.networkenvironment");
		ServerHelper::RemoteObjectPtr pNetworkEnvironmentServiceRemoteObject = ServerHelper::createRemoteObject(pNetworkEnvironmentService, oid);		
		_pServiceRef = pContext->registry().registerService(oid, pNetworkEnvironmentServiceRemoteObject, Properties());
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef = 0;
		ServerHelper::shutdown();
	}

private:
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::NetworkEnvironment


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::NetworkEnvironment::BundleActivator)
POCO_END_MANIFEST
