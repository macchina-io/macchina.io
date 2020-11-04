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
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/LoggingRegistry.h"
#include "Poco/EventChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/ClassLibrary.h"
#include "ConsoleRequestHandler.h"


namespace IoT {
namespace Web {
namespace Console {


class ConsoleRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
	{
		return new ConsoleRequestHandler(_pChannel, context());
	}
	
protected:
	void initImpl()
	{
		Poco::EventChannel* pEventChannel = 0;
		Poco::LoggingRegistry& registry = Poco::LoggingRegistry::defaultRegistry();
		try
		{
			Poco::Channel* pChannel = registry.channelForName("webconsole");
			pEventChannel = dynamic_cast<Poco::EventChannel*>(pChannel);
		}
		catch (Poco::NotFoundException&)
		{
			// handled below
		}
		catch (Poco::Exception& exc)
		{
			context()->logger().log(exc);
		}
		if (pEventChannel)
		{
			_pChannel.assign(pEventChannel, true);
		}
		else
		{
			context()->logger().warning("No EventChannel named \"webconsole\" found.");
			_pChannel = new Poco::EventChannel;
		}
	}

private:
	Poco::AutoPtr<Poco::EventChannel> _pChannel;
};


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
	}
		
	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		ConsoleRequestHandler::stopAll();
	}
};


} } } // namespace IoT::Web::Console


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Web::Console::BundleActivator)
POCO_END_MANIFEST


POCO_BEGIN_NAMED_MANIFEST(WebServer, Poco::OSP::Web::WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::Console::ConsoleRequestHandlerFactory)
POCO_END_MANIFEST
