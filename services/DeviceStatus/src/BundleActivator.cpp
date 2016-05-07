//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/DeviceStatus/DeviceStatusServiceImpl.h"
#include "IoT/DeviceStatus/DeviceStatusServiceServerHelper.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;


namespace IoT {
namespace DeviceStatus {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::DeviceStatus::DeviceStatusService> ServerHelper;
		
		Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pDeviceStatusService = new DeviceStatusServiceImpl(pContext);
		std::string oid("io.macchina.services.devicestatus");
		ServerHelper::RemoteObjectPtr pDeviceStatusServiceRemoteObject = ServerHelper::createRemoteObject(pDeviceStatusService, oid);		
		_pServiceRef = pContext->registry().registerService(oid, pDeviceStatusServiceRemoteObject, Properties());
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef = 0;
	}

private:
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::DeviceStatus


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::DeviceStatus::BundleActivator)
POCO_END_MANIFEST
