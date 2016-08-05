//
// DeviceStatusServiceRemoteObject.h
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusServiceRemoteObject_INCLUDED
#define IoT_DeviceStatus_DeviceStatusServiceRemoteObject_INCLUDED


#include "IoT/DeviceStatus/IDeviceStatusService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceRemoteObject: public IoT::DeviceStatus::IDeviceStatusService, public Poco::RemotingNG::RemoteObject
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	typedef Poco::AutoPtr<DeviceStatusServiceRemoteObject> Ptr;

	DeviceStatusServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject);
		/// Creates a DeviceStatusServiceRemoteObject.

	virtual ~DeviceStatusServiceRemoteObject();
		/// Destroys the DeviceStatusServiceRemoteObject.

	IoT::DeviceStatus::DeviceStatus acknowledge(int id);
		/// Marks the message with the given ID as acknowledged.
		///
		/// Returns the new device status.

	IoT::DeviceStatus::DeviceStatus clearStatus(const std::string& messageClass);
		/// Clears the status update with the given messageClass
		/// and removes it from the message history.
		///
		/// Returns the new device status.

	std::vector < IoT::DeviceStatus::StatusMessage > messages(int maxMessages = int(0)) const;
		/// Retrieves stored status messages. If maxMessages is > 0, will at most
		/// return maxMessages messages.

	IoT::DeviceStatus::DeviceStatusChange postStatus(const IoT::DeviceStatus::StatusUpdate& statusUpdate);
		/// Updates the device status. The given statusId in statusUpdate should uniquely 
		/// identify this status update, and is used to clear it at a later time with 
		/// clearStatus(), or to coalesce status updates.
		///
		/// statusId can also be an empty string. However, in this case the status cannot
		/// be cleared or coalesced with another update at a later time.
		///
		/// Returns a DeviceStatusChange structure.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	IoT::DeviceStatus::DeviceStatus remove(int id);
		/// Removes the message with the given ID from the message history.
		///
		/// Returns the new device status.

	virtual void reset();
		/// Resets the device status to DEVICE_STATUS_OK and removes all messages.

	IoT::DeviceStatus::DeviceStatus status() const;
		/// Returns the current device status.
		///
		/// Only unacknowledged status updates are considered in determining
		/// the current status.

protected:
	void event__statusChanged(const IoT::DeviceStatus::DeviceStatusChange& data);

	void event__statusUpdated(const IoT::DeviceStatus::DeviceStatusChange& data);

private:
	Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> _pServiceObject;
};


inline IoT::DeviceStatus::DeviceStatus DeviceStatusServiceRemoteObject::acknowledge(int id)
{
	return _pServiceObject->acknowledge(id);
}


inline IoT::DeviceStatus::DeviceStatus DeviceStatusServiceRemoteObject::clearStatus(const std::string& messageClass)
{
	return _pServiceObject->clearStatus(messageClass);
}


inline std::vector < IoT::DeviceStatus::StatusMessage > DeviceStatusServiceRemoteObject::messages(int maxMessages) const
{
	return _pServiceObject->messages(maxMessages);
}


inline IoT::DeviceStatus::DeviceStatusChange DeviceStatusServiceRemoteObject::postStatus(const IoT::DeviceStatus::StatusUpdate& statusUpdate)
{
	return _pServiceObject->postStatus(statusUpdate);
}


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceStatusServiceRemoteObject::remoting__typeId() const
{
	return IDeviceStatusService::remoting__typeId();
}


inline IoT::DeviceStatus::DeviceStatus DeviceStatusServiceRemoteObject::remove(int id)
{
	return _pServiceObject->remove(id);
}


inline void DeviceStatusServiceRemoteObject::reset()
{
	_pServiceObject->reset();
}


inline IoT::DeviceStatus::DeviceStatus DeviceStatusServiceRemoteObject::status() const
{
	return _pServiceObject->status();
}


} // namespace DeviceStatus
} // namespace IoT


#endif // IoT_DeviceStatus_DeviceStatusServiceRemoteObject_INCLUDED

