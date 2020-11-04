//
// CounterEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CounterEventDispatcher_INCLUDED
#define IoT_Devices_CounterEventDispatcher_INCLUDED


#include "IoT/Devices/CounterRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class CounterEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// A counter counts events.
{
public:
	CounterEventDispatcher(CounterRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a CounterEventDispatcher.

	virtual ~CounterEventDispatcher();
		/// Destroys the CounterEventDispatcher.

	void event__countChanged(const void* pSender, const Poco::Int32& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__countChangedImpl(const std::string& subscriberURI, const Poco::Int32& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	CounterRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CounterEventDispatcher::remoting__typeId() const
{
	return ICounter::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CounterEventDispatcher_INCLUDED

