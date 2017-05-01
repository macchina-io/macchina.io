//
// TimeServiceProxy.h
//
// Package: Generated
// Module:  TimeServiceProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TimeServiceProxy_INCLUDED
#define TimeServiceProxy_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "TimeServiceRemoteObject.h"


namespace Services {


class TimeServiceProxy: public Services::TimeServiceRemoteObject, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<TimeServiceProxy> Ptr;

	TimeServiceProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a TimeServiceProxy.

	virtual ~TimeServiceProxy();
		/// Destroys the TimeServiceProxy.

	Poco::DateTime currentTime() const;
		/// Returns the current date and time.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	void wakeMeUp(const Poco::DateTime& time, const std::string& message);
		/// Schedules a wakeup call.
		///
		/// Fires the wakeUp event at the given time, passing
		/// the given message as argument.

private:
	static const std::string DEFAULT_NS;
	mutable Poco::DateTime _currentTimeRet;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


} // namespace Services


#endif // TimeServiceProxy_INCLUDED

