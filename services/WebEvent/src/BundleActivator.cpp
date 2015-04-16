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


#include "IoT/WebEvent/WebEventNotifierImpl.h"
#include "IoT/WebEvent/WebEventNotifierServerHelper.h"
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
namespace WebEvent {


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
		typedef Poco::RemotingNG::ServerHelper<IoT::WebEvent::WebEventNotifier> ServerHelper;
		
		Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pWebEventNotifier = new WebEventNotifierImpl(pContext);
		std::string oid("io.macchina.services.webeventnotifier");
		ServerHelper::RemoteObjectPtr pWebEventNotifierRemoteObject = ServerHelper::createRemoteObject(pWebEventNotifier, oid);		
		_pServiceRef = pContext->registry().registerService(oid, pWebEventNotifierRemoteObject, Properties());
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef = 0;
	}

private:
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::WebEvent


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::WebEvent::BundleActivator)
POCO_END_MANIFEST
