//
// WebEventNotifierImpl.cpp
//
// Library: IoT/WebEvent
// Package: WebEventNotifier
// Module:  WebEventNotifierImpl
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/WebEvent/WebEventNotifierImpl.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/RemotingNG/Context.h"
#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RegularExpression.h"
#include "Poco/Delegate.h"


using namespace std::string_literals;


namespace IoT {
namespace WebEvent {


class SubjectNameFilter: public Poco::RemotingNG::EventFilter<EventNotification>
{
public:
	SubjectNameFilter(const std::string& subjectName):
		_subjectName(subjectName)
	{
	}
	
	// EventFilter
	bool accept(const EventNotification& value)
	{
		if (value.subjectName == _subjectName)
		{
			return true;
		}
		else
		{
			return value.subjectName.length() > _subjectName.length() 
				&& value.subjectName.compare(0, _subjectName.length(), _subjectName) == 0
				&& value.subjectName[_subjectName.length()] == '.';
		}
	}
	
private:
	const std::string _subjectName;
};


class SubjectRegularExpressionFilter: public Poco::RemotingNG::EventFilter<EventNotification>
{
public:
	SubjectRegularExpressionFilter(const std::string& regex):
		_regex(regex)
	{
	}
	
	// EventFilter
	bool accept(const EventNotification& value)
	{
		return _regex.match(value.subjectName);
	}
	
private:
	const Poco::RegularExpression _regex;
};


WebEventNotifierImpl::WebEventNotifierImpl(Poco::OSP::BundleContext::Ptr pContext):
	_pWebEventService(Poco::OSP::ServiceFinder::find<Poco::OSP::WebEvent::WebEventService>(pContext))
{
	_pWebEventService->notificationSent += Poco::delegate(this, &WebEventNotifierImpl::onEvent);
}

	
WebEventNotifierImpl::~WebEventNotifierImpl()
{
	_pWebEventService->notificationSent -= Poco::delegate(this, &WebEventNotifierImpl::onEvent);
}


void WebEventNotifierImpl::notify(const std::string& subject, const std::string& data)
{
	_pWebEventService->notify(subject, data);
}


void WebEventNotifierImpl::onEvent(const Poco::OSP::WebEvent::WebEventService::NotificationEvent& ev)
{
	EventNotification en;
	en.subjectName = ev.first;
	en.data = ev.second;
	event(en);
}


void WebEventNotifierImpl::setEventSubjectNameFilter(const std::string& subscriberURI, const std::string& subjectName)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->setEventFilter<EventNotification>(subscriberURI, "event"s, new SubjectNameFilter(subjectName));
}


void WebEventNotifierImpl::setEventSubjectRegexFilter(const std::string& subscriberURI, const std::string& regex)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->setEventFilter<EventNotification>(subscriberURI, "event"s, new SubjectRegularExpressionFilter(regex));
}


void WebEventNotifierImpl::clearEventFilter(const std::string& subscriberURI)
{
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	Poco::RemotingNG::Context::Ptr pContext = Poco::RemotingNG::Context::get();
	std::string uri = pContext->getValue<std::string>("uri"s);
	std::string proto = pContext->getValue<std::string>("transport"s);
	Poco::RemotingNG::EventDispatcher::Ptr pED = orb.findEventDispatcher(uri, proto);
	pED->removeEventFilter(subscriberURI, "event"s);
}


} } // namespace IoT::WebEvent
