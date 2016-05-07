//
// DeviceStatusServiceEventDispatcher.h
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusServiceEventDispatcher_INCLUDED
#define IoT_DeviceStatus_DeviceStatusServiceEventDispatcher_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusServiceRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	DeviceStatusServiceEventDispatcher(DeviceStatusServiceRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a DeviceStatusServiceEventDispatcher.

	virtual ~DeviceStatusServiceEventDispatcher();
		/// Destroys the DeviceStatusServiceEventDispatcher.

	void event__statusChanged(const void* pSender, const IoT::DeviceStatus::DeviceStatusChange& data);

	void event__statusUpdated(const void* pSender, const IoT::DeviceStatus::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::DeviceStatus::DeviceStatusChange& data);

	void event__statusUpdatedImpl(const std::string& subscriberURI, const IoT::DeviceStatus::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	DeviceStatusServiceRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceStatusServiceEventDispatcher::remoting__typeId() const
{
	return IDeviceStatusService::remoting__typeId();
}


} // namespace DeviceStatus
} // namespace IoT


#endif // IoT_DeviceStatus_DeviceStatusServiceEventDispatcher_INCLUDED

