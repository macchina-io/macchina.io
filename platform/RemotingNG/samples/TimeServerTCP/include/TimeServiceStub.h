//
// TimeServiceStub.h
//
// Package: Generated
// Module:  TimeServiceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TimeServiceStub_INCLUDED
#define TimeServiceStub_INCLUDED


#include "Poco/SharedPtr.h"
#include "TimeServiceRemoteObject.h"


namespace Services {


class TimeServiceStub: public Services::TimeServiceRemoteObject
{
public:
	typedef Poco::AutoPtr<TimeServiceStub> Ptr;

	TimeServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Services::TimeService> pServiceObject);
		/// Creates a TimeServiceStub.

	virtual ~TimeServiceStub();
		/// Destroys the TimeServiceStub.

	Poco::DateTime currentTime() const;
		/// Returns the current date and time.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	void wakeMeUp(const Poco::DateTime& time, const std::string& message);
		/// Schedules a wakeup call.
		///
		/// Fires the wakeUp event at the given time, passing
		/// the given message as argument.

protected:
	void event__wakeUp(const std::string& data);

private:
	Poco::SharedPtr<Services::TimeService> _pServiceObject;
};


inline Poco::DateTime TimeServiceStub::currentTime() const
{
	return _pServiceObject->currentTime();
}


inline const Poco::RemotingNG::Identifiable::TypeId& TimeServiceStub::remoting__typeId() const
{
	return ITimeService::remoting__typeId();
}


inline void TimeServiceStub::wakeMeUp(const Poco::DateTime& time, const std::string& message)
{
	_pServiceObject->wakeMeUp(time, message);
}


} // namespace Services


#endif // TimeServiceStub_INCLUDED

