//
// DeviceStatusService.h
//
// $Id$
//
// Library: IoT/DeviceStatus
// Package: DeviceStatusService
// Module:  DeviceStatusService
//
// Definition of the DeviceStatusService interface.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusService_INCLUDED
#define IoT_DeviceStatus_DeviceStatusService_INCLUDED


#include "IoT/DeviceStatus/DeviceStatus.h"
#include "Poco/BasicEvent.h"
#include "Poco/DateTime.h"
#include "Poco/Optional.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace DeviceStatus {


enum DeviceStatus
{
	DEVICE_STATUS_OK       = 0,
		/// The device is working properly. Informational messages
		/// may be available.
		
	DEVICE_STATUS_NOTICE   = 1,
		/// The device is working properly, but one or more 
		/// messages that need to be acknowledged are available.
		///
		/// Example: a software update is available
		
	DEVICE_STATUS_WARNING  = 2,
		/// The device is working properly, but one or more 
		/// messages that may indicate an upcoming problem are
		/// available.

	DEVICE_STATUS_ERROR    = 3,
		/// The device has detected a malfunction, but continues
		/// to operate with minor or no restrictions.
		///
		/// Example: a temporary interruption of a network connection

	DEVICE_STATUS_CRITICAL = 4,
		/// The device has detected a malfunction that prevents
		/// it from performing its function. 
		///
		/// Example: no or invalid data received from a sensor
		
	DEVICE_STATUS_FATAL    = 5
		/// The device has detected a malfunction that prevents
		/// it from performing its function. 
		///
		/// Example: hardware failure
};


//@ serialize
struct StatusUpdate
{
	StatusUpdate():
		acknowledgeable(true),
		status(DEVICE_STATUS_OK)
	{
	}
	
	//@ mandatory=false
	std::string messageClass;
		/// An string that identifies the message class.
		///
		/// If non-empty, any previously posted message
		/// with the same class will be removed before
		/// the new message is added. Therefore, at most
		/// one message of a given non-empty message class
		/// is stored.
	
	//@ mandatory = false	
	std::string source;
		/// Optional source of the status update. Can be
		/// an application specific name of a subsystem or device.
		
	//@ mandatory = false
	bool acknowledgeable;
		/// Optional flag denoting whether the status update can
		/// be acknowledged by the user. Once a status update has
		/// been acknowledged, it will no longer affect the 
		/// global (or source-specific) device status.
		///
		/// Defaults to true.
		 
	DeviceStatus status;
		/// New device status.

	std::string text;
		/// The message text.
};


//@ serialize
struct StatusMessage
	/// A device status message.
{
	StatusMessage():
		id(0),
		status(DEVICE_STATUS_OK),
		acknowledgeable(false),
		acknowledged(false)
	{
	}

	Poco::Int64 id;
		/// An internally assigned integer that identifies the message.
		/// Used with acknowledge() and remove().

	std::string messageClass;
		/// An string that identifies the message class.
		///
		/// If non-empty, any previously posted message
		/// with the same class will be removed before
		/// the new message is added. Therefore, at most
		/// one message of a given non-empty message class
		/// is stored.
		
	std::string source;
		/// Optional source of the status update. Can be
		/// an application specific name of a subsystem or device.
		 
	DeviceStatus status;
		/// New device status.

	std::string text;
		/// The message text.

	Poco::DateTime timestamp;
		/// Date and time of the message.
		
	bool acknowledgeable;
		/// Flag denoting whether the status update can
		/// be acknowledged by the user. 

	bool acknowledged;
		/// True if message has been acknowledged by user, otherwise false.
		///
		/// Once a status update has been acknowledged, it will no longer 
		/// affect the global (or source-specific) device status.
};


//@ serialize
struct DeviceStatusChange
{
	DeviceStatusChange():
		currentStatus(DEVICE_STATUS_OK),
		previousStatus(DEVICE_STATUS_OK)
	{
	}

	Poco::Optional<StatusMessage> message;
	DeviceStatus currentStatus;
	DeviceStatus previousStatus;
};


//@ remote
class IoTDeviceStatus_API DeviceStatusService
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	typedef Poco::SharedPtr<DeviceStatusService> Ptr;
	typedef Poco::UInt32 StatusID;
	
	Poco::BasicEvent<const DeviceStatusChange> statusChanged;
		/// Fired when the device status level has changed.
		/// Not every call to postStatus() or postStatusAsync() 
		/// will trigger a statusChanged event.

	Poco::BasicEvent<const DeviceStatusChange> statusUpdated;
		/// Fired when the device status has been updated
		/// by calling postStatus() or postStatusAsync(), 
		/// regardless of whether the device status level 
		/// has changed or not.

	DeviceStatusService();
		/// Creates the DeviceStatusService.
		
	virtual ~DeviceStatusService();
		/// Destroys the DeviceStatusService.
		
	virtual DeviceStatus status() const = 0;
		/// Returns the current global device status.
		///
		/// Only unacknowledged status updates are considered in determining
		/// the current status.

	virtual DeviceStatus statusOfSource(const std::string& source) const = 0;
		/// Returns the current source-specific device status, considering 
		/// only status updates with the given source.
		///
		/// Only unacknowledged status updates are considered in determining
		/// the current status.
		
	virtual DeviceStatusChange postStatus(const StatusUpdate& statusUpdate) = 0;
		/// Updates the device status. 
		///
		/// Returns a DeviceStatusChange structure.

	virtual void postStatusAsync(const StatusUpdate& statusUpdate) = 0;
		/// Updates the device status asynchronously.
		///
		/// The actual status update in the database will be done 
		/// asynchronously in a separate thread.
		
	virtual DeviceStatus clearStatus(const std::string& messageClass) = 0;
		/// Clears the status update with the given messageClass
		/// and removes it from the message history.
		///
		/// Returns the new device status.

	virtual DeviceStatus clearStatusOfSource(const std::string& source) = 0;
		/// Clears all status updates with the given source
		/// and removes them from the message history.
		///
		/// Returns the new device status.
		
	virtual DeviceStatus acknowledge(Poco::Int64 id) = 0;
		/// Marks the message with the given ID as acknowledged, if it is
		/// acknowledgeable.
		///
		/// Returns the new device status.

	virtual DeviceStatus acknowledgeUpTo(Poco::Int64 id) = 0;
		/// Marks all acknowledgeable messages up to (and including) 
		/// the given ID as acknowledged.
		///
		/// Returns the new device status.

	virtual DeviceStatus remove(Poco::Int64 id) = 0;
		/// Removes the message with the given ID from the message history.
		///
		/// Returns the new device status.
	
	//@ $maxMessages={mandatory=false}
	virtual std::vector<StatusMessage> messages(int maxMessages = 0) const = 0;
		/// Retrieves stored status messages. If maxMessages is > 0, will at most
		/// return maxMessages messages.
		
	virtual void reset() = 0;
		/// Resets the device status to DEVICE_STATUS_OK and removes all messages.
};


} } // namespace IoT::DeviceStatus


#endif // IoT_DeviceStatus_DeviceStatusService_INCLUDED
