//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/PreferencesService.h"
#include "IoT/Dataflow/Runner/CoreNodeFactoryService.h"
#include "IoT/Dataflow/Runner/OutputNode.h"
#include "IoT/Dataflow/Runner/DataflowExtensionPoint.h"
#include "Poco/ClassLibrary.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
	
		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(_pContext);
		_pXPS = Poco::OSP::ServiceFinder::find<Poco::OSP::ExtensionPointService>(_pContext);

		DataflowExtensionPoint::Ptr pDataflowXP = new DataflowExtensionPoint(pContext);
		_pXPS->registerExtensionPoint(pContext->thisBundle(), "io.macchina.dataflow", pDataflowXP);
		
		CoreNodeFactoryService::Ptr pCoreNodeFactoryService = new CoreNodeFactoryService;
		Poco::OSP::Properties props;
		props.set("io.macchina.dataflow.nodetype", "core");
		_pCoreNodeFactoryServiceRef = _pContext->registry().registerService("io.macchina.dataflow.nodefactory.core", pCoreNodeFactoryService, props);

		OutputNodeFactoryService::Ptr pOutputNodeFactoryService = new OutputNodeFactoryService;
		props.set("io.macchina.dataflow.nodetype", "io.macchina.dataflow.output");
		_pOutputNodeFactoryServiceRef = _pContext->registry().registerService("io.macchina.dataflow.nodefactory.output", pOutputNodeFactoryService, props);
	}
		
	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pXPS->unregisterExtensionPoint("io.macchina.dataflow");
		_pContext->registry().unregisterService(_pCoreNodeFactoryServiceRef);
		_pContext->registry().unregisterService(_pOutputNodeFactoryServiceRef);

		_pXPS = 0;
		_pPrefs = 0;
	
		_pContext = 0;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ExtensionPointService::Ptr _pXPS;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
	Poco::OSP::ServiceRef::Ptr _pCoreNodeFactoryServiceRef;
	Poco::OSP::ServiceRef::Ptr _pOutputNodeFactoryServiceRef;
};


} } } // namespace IoT::Dataflow::Runner


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Dataflow::Runner::BundleActivator)
POCO_END_MANIFEST
