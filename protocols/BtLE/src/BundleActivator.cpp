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
#include "IoT/BtLE/PeripheralManagerImpl.h"
#include "IoT/BtLE/PeripheralManagerServerHelper.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;


namespace IoT {
namespace BtLE {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	using ServerHelper = Poco::RemotingNG::ServerHelper<PeripheralManager>;

	void start(BundleContext::Ptr pContext)
	{
		PeripheralManagerImpl::Ptr pPeripheralManager = new PeripheralManagerImpl(pContext->registry());
		std::string oid("io.macchina.btle.peripheralmanager");
		ServerHelper::RemoteObjectPtr pMailerServiceRemoteObject = ServerHelper::createRemoteObject(pPeripheralManager, oid);		
		_pServiceRef = pContext->registry().registerService(oid, pMailerServiceRemoteObject, Properties());
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef.reset();
		ServerHelper::shutdown();
	}

private:
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::BtLE


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::BtLE::BundleActivator)
POCO_END_MANIFEST
