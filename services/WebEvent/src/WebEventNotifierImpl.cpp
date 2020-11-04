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


namespace IoT {
namespace WebEvent {


WebEventNotifierImpl::WebEventNotifierImpl(Poco::OSP::BundleContext::Ptr pContext):
	_pWebEventService(Poco::OSP::ServiceFinder::find<Poco::OSP::WebEvent::WebEventService>(pContext))
{
}

	
WebEventNotifierImpl::~WebEventNotifierImpl()
{
}


void WebEventNotifierImpl::notify(const std::string& subject, const std::string& data)
{
	_pWebEventService->notify(subject, data);
}


} } // namespace IoT::WebEvent
