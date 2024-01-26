//
// WebEventNotifierImpl.h
//
// Library: IoT/WebEvent
// Package: WebEventNotifier
// Module:  WebEventNotifierImpl
//
// Definition of the WebEventNotifierImpl class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebEvent_WebEventNotifierImpl_INCLUDED
#define IoT_WebEvent_WebEventNotifierImpl_INCLUDED


#include "IoT/WebEvent/WebEventNotifier.h"
#include "Poco/OSP/WebEvent/WebEventService.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace WebEvent {


class IoTWebEvent_API WebEventNotifierImpl: public WebEventNotifier
	/// The implementation of the WebEventNotifier interface.
{
public:
	using Ptr = Poco::AutoPtr<WebEventNotifierImpl>;

	WebEventNotifierImpl(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the Device.

	~WebEventNotifierImpl();
		/// Destroys the Device.

	// WebEventNotifier
	void notify(const std::string& subjectName, const std::string& data);
	void setEventSubjectNameFilter(const std::string& subscriberURI, const std::string& subjectName);
	void setEventSubjectRegexFilter(const std::string& subscriberURI, const std::string& regex);
	void clearEventFilter(const std::string& subscriberURI);

protected:
	void onEvent(const Poco::OSP::WebEvent::WebEventService::NotificationEvent& event);

private:
	Poco::OSP::WebEvent::WebEventService::Ptr _pWebEventService;
};


} } // namespace IoT::WebEvent


#endif // IoT_WebEvent_WebEventNotifierImpl_INCLUDED
