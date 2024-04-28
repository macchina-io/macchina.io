//
// CounterDatapointEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterDatapointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CounterDatapointEventDispatcher_INCLUDED
#define IoT_Devices_CounterDatapointEventDispatcher_INCLUDED


#include "IoT/Devices/ICounterDatapoint.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class CounterDatapointEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for datapoints holding a counter
	/// (a 64-bit unsigned integer).
	///
	/// In addition to the methods defined in this interface,
	/// a CounterDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	CounterDatapointEventDispatcher(ICounterDatapoint* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a CounterDatapointEventDispatcher.

	virtual ~CounterDatapointEventDispatcher();
		/// Destroys the CounterDatapointEventDispatcher.

	void event__invalidated(const void* pSender);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const void* pSender, const Poco::Int64& data);

	void event__valueChanged(const void* pSender, const Poco::Int64& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__invalidatedImpl(const std::string& subscriberURI);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	void event__validatedImpl(const std::string& subscriberURI, const Poco::Int64& data);

	void event__valueChangedImpl(const std::string& subscriberURI, const Poco::Int64& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	ICounterDatapoint* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CounterDatapointEventDispatcher::remoting__typeId() const
{
	return ICounterDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CounterDatapointEventDispatcher_INCLUDED

