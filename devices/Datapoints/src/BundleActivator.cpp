//
// BundleActivator.cpp
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/DatapointFactoryImpl.h"
#include "IoT/Datapoints/DatapointFactoryServerHelper.h"
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
namespace Datapoints {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	Poco::OSP::ServiceRef::Ptr createDatapointFactory()
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Datapoints::DatapointFactory> ServerHelper;

		Poco::SharedPtr<DatapointFactory> pDatapointFactory = new DatapointFactoryImpl(_pContext);
		ServerHelper::RemoteObjectPtr pDatapointFactoryRemoteObject = ServerHelper::createRemoteObject(pDatapointFactory, "io.macchina.datapoint-factory"s);

		Properties props;
		return _pContext->registry().registerService("io.macchina.datapoint-factory"s, pDatapointFactoryRemoteObject, props);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;

		_pDatapointFactoryRef = createDatapointFactory();
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		_pContext->registry().unregisterService(_pDatapointFactoryRef);
		_pDatapointFactoryRef.reset();
		_pContext.reset();
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ServiceRef::Ptr _pDatapointFactoryRef;
};


} } // namespace IoT::Datapoints


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Datapoints::BundleActivator)
POCO_END_MANIFEST
