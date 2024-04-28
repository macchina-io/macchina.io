//
// StringDatapointEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  StringDatapointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_StringDatapointEventDispatcher_INCLUDED
#define IoT_Devices_StringDatapointEventDispatcher_INCLUDED


#include "IoT/Devices/IStringDatapoint.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class StringDatapointEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for datapoints holding a string value.
	///
	/// In addition to the methods defined in this interface,
	/// a StringDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	StringDatapointEventDispatcher(IStringDatapoint* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a StringDatapointEventDispatcher.

	virtual ~StringDatapointEventDispatcher();
		/// Destroys the StringDatapointEventDispatcher.

	void event__invalidated(const void* pSender);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const void* pSender, const std::string& data);

	void event__valueChanged(const void* pSender, const std::string& data);

	void event__valueUpdated(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__invalidatedImpl(const std::string& subscriberURI);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	void event__validatedImpl(const std::string& subscriberURI, const std::string& data);

	void event__valueChangedImpl(const std::string& subscriberURI, const std::string& data);

	void event__valueUpdatedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	IStringDatapoint* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& StringDatapointEventDispatcher::remoting__typeId() const
{
	return IStringDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_StringDatapointEventDispatcher_INCLUDED

