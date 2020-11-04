//
// WebEventBundleActivator.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/WebEvent/WebEventService.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTaskAdapter.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;


class WebEventBundleActivator: public BundleActivator
{
public:
	WebEventBundleActivator()
	{
	}
	
	~WebEventBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pWebEventService = Poco::OSP::ServiceFinder::find<Poco::OSP::WebEvent::WebEventService>(pContext);
		_pWebEventService->notificationSent += Poco::delegate(this, &WebEventBundleActivator::onNotificationSent);
		_pWebEventService->requestReceived += Poco::delegate(this, &WebEventBundleActivator::onRequestReceived);
		_pWebEventService->subjectNotified("sample.tenSecondsTimer") += Poco::delegate(this, &WebEventBundleActivator::onSpecificNotificationSent);
		_pWebEventService->subjectNotified("sample.client") += Poco::delegate(this, &WebEventBundleActivator::onSpecificNotificationSent);

		_timer.scheduleAtFixedRate(new Poco::Util::TimerTaskAdapter<WebEventBundleActivator>(*this, &WebEventBundleActivator::fire10SecondsEvent), 10000, 10000);
		_timer.scheduleAtFixedRate(new Poco::Util::TimerTaskAdapter<WebEventBundleActivator>(*this, &WebEventBundleActivator::fire60SecondsEvent), 60000, 60000);
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		_pWebEventService->notificationSent -= Poco::delegate(this, &WebEventBundleActivator::onNotificationSent);
		_pWebEventService->requestReceived -= Poco::delegate(this, &WebEventBundleActivator::onRequestReceived);

		_timer.cancel(true);
		_pWebEventService = 0;
		_pContext = 0;
	}
	
	void fire10SecondsEvent(Poco::Util::TimerTask&)
	{
		fireEvent("sample.tenSecondsTimer");
	}
	
	void fire60SecondsEvent(Poco::Util::TimerTask&)
	{
		fireEvent("sample.sixtySecondsTimer");
	}
	
	void fireEvent(const std::string& subjectName)
	{
		_pWebEventService->notify(subjectName, Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FORMAT));
	}
	
	void onNotificationSent(const Poco::OSP::WebEvent::WebEventService::NotificationEvent& ev)
	{
		std::string msg("Notification sent, subject=");
		msg += ev.first;
		msg += ", data=";
		msg += ev.second;
		_pContext->logger().information(msg);
	}

	void onSpecificNotificationSent(const Poco::OSP::WebEvent::WebEventService::NotificationEvent& ev)
	{
		std::string msg("Specific Notification sent, subject=");
		msg += ev.first;
		msg += ", data=";
		msg += ev.second;
		_pContext->logger().information(msg);
	}
	
	void onRequestReceived(const Poco::Net::HTTPServerRequest*& pRequest)
	{
		_pContext->logger().information("WebSocket request from " + pRequest->clientAddress().toString());
	}
	
private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::Util::Timer _timer;
	Poco::OSP::WebEvent::WebEventService::Ptr _pWebEventService;
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(WebEventBundleActivator)
POCO_END_MANIFEST
