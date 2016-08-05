//
// IDeviceStatusService.h
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  IDeviceStatusService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_IDeviceStatusService_INCLUDED
#define IoT_DeviceStatus_IDeviceStatusService_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace DeviceStatus {


class IDeviceStatusService: public Poco::OSP::Service
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	typedef Poco::AutoPtr<IDeviceStatusService> Ptr;

	IDeviceStatusService();
		/// Creates a IDeviceStatusService.

	virtual ~IDeviceStatusService();
		/// Destroys the IDeviceStatusService.

	virtual IoT::DeviceStatus::DeviceStatus acknowledge(int id) = 0;
		/// Marks the message with the given ID as acknowledged.
		///
		/// Returns the new device status.

	virtual IoT::DeviceStatus::DeviceStatus clearStatus(const std::string& messageClass) = 0;
		/// Clears the status update with the given messageClass
		/// and removes it from the message history.
		///
		/// Returns the new device status.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::vector < IoT::DeviceStatus::StatusMessage > messages(int maxMessages = int(0)) const = 0;
		/// Retrieves stored status messages. If maxMessages is > 0, will at most
		/// return maxMessages messages.

	virtual IoT::DeviceStatus::DeviceStatusChange postStatus(const IoT::DeviceStatus::StatusUpdate& statusUpdate) = 0;
		/// Updates the device status. The given statusId in statusUpdate should uniquely 
		/// identify this status update, and is used to clear it at a later time with 
		/// clearStatus(), or to coalesce status updates.
		///
		/// statusId can also be an empty string. However, in this case the status cannot
		/// be cleared or coalesced with another update at a later time.
		///
		/// Returns a DeviceStatusChange structure.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual IoT::DeviceStatus::DeviceStatus remove(int id) = 0;
		/// Removes the message with the given ID from the message history.
		///
		/// Returns the new device status.

	virtual void reset() = 0;
		/// Resets the device status to DEVICE_STATUS_OK and removes all messages.

	virtual IoT::DeviceStatus::DeviceStatus status() const = 0;
		/// Returns the current device status.
		///
		/// Only unacknowledged status updates are considered in determining
		/// the current status.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const DeviceStatusChange > statusChanged;
	Poco::BasicEvent < const DeviceStatusChange > statusUpdated;
};


} // namespace DeviceStatus
} // namespace IoT


#endif // IoT_DeviceStatus_IDeviceStatusService_INCLUDED

