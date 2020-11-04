//
// ServiceListener.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::ServiceEvent;
using Poco::Delegate;


class ServiceListenerBundleActivator: public BundleActivator
	/// A very simple bundle that subscribes its
	/// BundleActivator to ServiceRegistry events
	/// and prints these events.
{
public:
	ServiceListenerBundleActivator()
	{
	}
	
	~ServiceListenerBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		// save BundleContext for later use
		_pContext = pContext;
		
		// write a startup message to the log
		std::string msg("Bundle ");
		msg.append(pContext->thisBundle()->name());
		msg.append(" started");
		pContext->logger().information(msg);
		
		// subscribe for ServiceRegistry events
		pContext->registry().serviceRegistered   += Delegate<ServiceListenerBundleActivator, ServiceEvent>(this, &ServiceListenerBundleActivator::handleServiceRegistered);
		pContext->registry().serviceUnregistered += Delegate<ServiceListenerBundleActivator, ServiceEvent>(this, &ServiceListenerBundleActivator::handleServiceUnregistered);
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		// write a shutdown message to the log
		std::string msg("Bundle ");
		msg.append(pContext->thisBundle()->name());
		msg.append(" stopped");
		pContext->logger().information(msg);
		
		// unsubscribe from ServiceRegistry events
		pContext->registry().serviceRegistered   -= Delegate<ServiceListenerBundleActivator, ServiceEvent>(this, &ServiceListenerBundleActivator::handleServiceRegistered);
		pContext->registry().serviceUnregistered -= Delegate<ServiceListenerBundleActivator, ServiceEvent>(this, &ServiceListenerBundleActivator::handleServiceUnregistered);
	}
	
protected:
	void handleServiceRegistered(const void* sender, ServiceEvent& event)
	{
		std::string msg("Service registered: ");
		msg.append(event.service()->name());
		_pContext->logger().information(msg);
	}

	void handleServiceUnregistered(const void* sender, ServiceEvent& event)
	{
		std::string msg("Service unregistered: ");
		msg.append(event.service()->name());
		_pContext->logger().information(msg);
	}
	
private:
	BundleContext::Ptr _pContext;
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(ServiceListenerBundleActivator)
POCO_END_MANIFEST
