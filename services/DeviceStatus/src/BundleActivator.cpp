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


#include "DeviceStatusServiceImpl.h"
#include "IoT/DeviceStatus/DeviceStatusServiceServerHelper.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/LoggingRegistry.h"
#include "Poco/EventChannel.h"
#include "Poco/Delegate.h"
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveDispatcher.h"
#include "Poco/ExpireLRUCache.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;


namespace IoT {
namespace DeviceStatus {


class BundleActivator: public Poco::OSP::BundleActivator, public Poco::ActiveDispatcher
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::DeviceStatus::DeviceStatusService> ServerHelper;


	BundleActivator():
		postStatusAsync(this, &BundleActivator::postStatusAsyncImpl),
		_messageCache(128, 30000)
	{
	}
	
	~BundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;

		Poco::OSP::PreferencesService::Ptr pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(pContext);
		
		int maxAgeHours = pPrefs->configuration()->getInt("deviceStatus.messages.maxAge", 30*24);
		
		Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pDeviceStatusService = new DeviceStatusServiceImpl(pContext, maxAgeHours);
		std::string oid("io.macchina.services.devicestatus");
		ServerHelper::RemoteObjectPtr pDeviceStatusServiceRemoteObject = ServerHelper::createRemoteObject(pDeviceStatusService, oid);		
		_pServiceRef = pContext->registry().registerService(oid, pDeviceStatusServiceRemoteObject, Properties());

		std::string channelName = pPrefs->configuration()->getString("deviceStatus.channel", "");
		if (!channelName.empty())
		{
			initEventChannel(channelName);
		}
		
		if (_pEventChannel)
		{
			_pEventChannel->messageLogged += Poco::delegate(this, &BundleActivator::onMessageLogged);
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		if (_pEventChannel)
		{
			_pEventChannel->messageLogged -= Poco::delegate(this, &BundleActivator::onMessageLogged);
		}

		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef = 0;
		_pDeviceStatusService = 0;
		_pContext = 0;
		
		ServerHelper::shutdown();
	}

protected:
	void initEventChannel(const std::string& channelName)
	{
		Poco::EventChannel* pEventChannel = 0;
		Poco::LoggingRegistry& registry = Poco::LoggingRegistry::defaultRegistry();
		try
		{
			Poco::Channel* pChannel = registry.channelForName(channelName);
			pEventChannel = dynamic_cast<Poco::EventChannel*>(pChannel);
		}
		catch (Poco::NotFoundException&)
		{
			// handled below
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().log(exc);
		}
		if (pEventChannel)
		{
			_pContext->logger().information("Listening to log messages on channel \"%s\".", channelName);
			_pEventChannel.assign(pEventChannel, true);
		}
		else
		{
			_pContext->logger().warning("No EventChannel named \"%s\" found.", channelName);
		}
	}
	
	void onMessageLogged(const Poco::Message& message)
	{
		switch (message.getPriority())
		{
		case Poco::Message::PRIO_FATAL:
			updateDeviceStatus(message, DEVICE_STATUS_FATAL);
			break;
		case Poco::Message::PRIO_CRITICAL:
			updateDeviceStatus(message, DEVICE_STATUS_CRITICAL);
			break;
		case Poco::Message::PRIO_ERROR:
			updateDeviceStatus(message, DEVICE_STATUS_ERROR);
			break;
		case Poco::Message::PRIO_WARNING:
			updateDeviceStatus(message, DEVICE_STATUS_WARNING);
			break;
		case Poco::Message::PRIO_NOTICE:
		case Poco::Message::PRIO_INFORMATION:
		case Poco::Message::PRIO_DEBUG:
		case Poco::Message::PRIO_TRACE:
			// ignore
			break;
		}
	}
	
	void updateDeviceStatus(const Poco::Message& message, DeviceStatus status)
	{
		try
		{
			std::string text = message.getSource();
			text += ": ";
			text += message.getText();
			
			if (!_messageCache.has(text))
			{
				StatusUpdate update;
				update.status = status;
				update.source = message.getSource();
				update.text = message.getText();

				postStatusAsync(update);
				_messageCache.update(text, 0);
			}
		}
		catch (...)
		{
		}
	}

	void postStatusAsyncImpl(const StatusUpdate& update)
	{
		try
		{
			_pDeviceStatusService->postStatus(update);
		}
		catch (...)
		{
		}
	}
	
	Poco::ActiveMethod<void, StatusUpdate, BundleActivator, Poco::ActiveStarter<Poco::ActiveDispatcher> > postStatusAsync;

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> _pDeviceStatusService;
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
	Poco::AutoPtr<Poco::EventChannel> _pEventChannel;
	Poco::ExpireLRUCache<std::string, int> _messageCache;
};


} } // namespace IoT::DeviceStatus


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::DeviceStatus::BundleActivator)
POCO_END_MANIFEST
