//
// WebEventNotifierImpl.h
//
// $Id$
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
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::AutoPtr<WebEventNotifierImpl> Ptr;

	WebEventNotifierImpl(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the Device.
		
	~WebEventNotifierImpl();
		/// Destroys the Device.
	
	// WebEventNotifier	
	 void notify(const std::string& subjectName, const std::string& data);
	 
private:
	Poco::OSP::WebEvent::WebEventService::Ptr _pWebEventService;
};


} } // namespace IoT::WebEvent


#endif // IoT_WebEvent_WebEventNotifierImpl_INCLUDED
