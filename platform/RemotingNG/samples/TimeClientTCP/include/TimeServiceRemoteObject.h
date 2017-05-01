//
// TimeServiceRemoteObject.h
//
// Package: Generated
// Module:  TimeServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TimeServiceRemoteObject_INCLUDED
#define TimeServiceRemoteObject_INCLUDED


#include "ITimeService.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace Services {


class TimeServiceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public Services::ITimeService
{
public:
	typedef Poco::AutoPtr<TimeServiceRemoteObject> Ptr;

	TimeServiceRemoteObject();
		/// Creates a TimeServiceRemoteObject.

	virtual ~TimeServiceRemoteObject();
		/// Destroys the TimeServiceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& TimeServiceRemoteObject::remoting__typeId() const
{
	return ITimeService::remoting__typeId();
}


} // namespace Services


#endif // TimeServiceRemoteObject_INCLUDED

