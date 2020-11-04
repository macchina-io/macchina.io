//
// ServiceEvent.cpp
//
// Library: OSP
// Package: Service
// Module:  ServiceEvent
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/ServiceEvent.h"


namespace Poco {
namespace OSP {


ServiceEvent::ServiceEvent(ServiceRef::Ptr pService, EventKind what):
	_pService(pService),
	_what(what)
{
}


ServiceEvent::ServiceEvent(const ServiceEvent& event):
	_pService(event._pService),
	_what(event._what)
{
}


ServiceEvent::~ServiceEvent()
{
}

	
ServiceEvent& ServiceEvent::operator = (const ServiceEvent& event)
{
	if (this != &event)
	{
		_pService = event._pService;
		_what     = event._what;
	}
	return *this;
}


} } // namespace Poco::OSP
