//
// ServiceEvent.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/ServiceEvent.h#1 $
//
// Library: OSP
// Package: Service
// Module:  ServiceEvent
//
// Definition of the ServiceEvent class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_ServiceEvent_INCLUDED
#define OSP_ServiceEvent_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/ServiceRef.h"


namespace Poco {
namespace OSP {


class OSP_API ServiceEvent
	/// The ServiceEvent class holds information about
	/// an event caused by a change to a service registration.
{
public:
	enum EventKind
	{
		EV_SERVICE_REGISTERED,
		EV_SERVICE_UNREGISTERED
	};
	
	ServiceEvent(ServiceRef::Ptr pService, EventKind what);
		/// Creates the ServiceEvent.
	
	ServiceEvent(const ServiceEvent& event);
		/// Creates the ServiceEvent by copying another one.
	
	~ServiceEvent();
		/// Destroys the ServiceEvent.
		
	ServiceEvent& operator = (const ServiceEvent& event);
		/// Assigns another ServiceEvent.
	
	ServiceRef::ConstPtr service() const;
		/// Returns the service that caused the event.
		
	EventKind what() const;
		/// Returns the reason of the event.

private:
	ServiceEvent();
	
	ServiceRef::Ptr _pService;
	EventKind       _what;
};


//
// inlines
//
inline ServiceRef::ConstPtr ServiceEvent::service() const
{
	return _pService;
}


inline ServiceEvent::EventKind ServiceEvent::what() const
{
	return _what;
}


} } // namespace Poco::OSP


#endif // OSP_ServiceEvent_INCLUDED
