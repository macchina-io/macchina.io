//
// BundleActivator.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceTreeServerHelper.h"
#include "IoT/Devices/DeviceTreeImpl.h"
#include "IoT/Devices/CompositeServerHelper.h"
#include "IoT/Devices/CompositeImpl.h"
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
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using namespace std::string_literals;


namespace IoT {
namespace Devices {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}

	Poco::OSP::ServiceRef::Ptr createDeviceTree()
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::DeviceTree> ServerHelper;

		Poco::SharedPtr<DeviceTree> pDeviceTree = new DeviceTreeImpl(_pContext->registry());
		ServerHelper::RemoteObjectPtr pDeviceTreeRemoteObject = ServerHelper::createRemoteObject(pDeviceTree, "io.macchina.deviceTree"s);

		Properties props;
		return _pContext->registry().registerService("io.macchina.deviceTree"s, pDeviceTreeRemoteObject, props);
	}

	Poco::OSP::ServiceRef::Ptr createRoot()
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Composite> ServerHelper;

		Poco::SharedPtr<Composite> pComposite = new CompositeImpl("io.macchina.composite.root"s, "/"s, _pContext->registry());
		ServerHelper::RemoteObjectPtr pCompositeRemoteObject = ServerHelper::createRemoteObject(pComposite, "io.macchina.composite.root"s);

		Properties props;
		props.set("io.macchina.device"s, "io.macchina.composite"s);
		props.set("io.macchina.nodeName"s, "/"s);
		return _pContext->registry().registerService("io.macchina.composite.root"s, pCompositeRemoteObject, props);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;

		_pDeviceTreeRef = createDeviceTree();
		_pRootRef = createRoot();
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		_pContext->registry().unregisterService(_pDeviceTreeRef);
		_pDeviceTreeRef.reset();
		_pContext->registry().unregisterService(_pRootRef);
		_pRootRef.reset();
		_pContext.reset();
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ServiceRef::Ptr _pDeviceTreeRef;
	Poco::OSP::ServiceRef::Ptr _pRootRef;
};


} } // namespace IoT::Devices


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Devices::BundleActivator)
POCO_END_MANIFEST
