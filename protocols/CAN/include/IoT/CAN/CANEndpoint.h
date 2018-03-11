//
// CANEndpoint.h
//
// Library: IoT/CAN
// Package: CANEndpoint
// Module:  CANEndpoint
///
/// Definition of the CANEndpoint interface.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_CANEndpoint_INCLUDED
#define IoT_CAN_CANEndpoint_INCLUDED


#include "IoT/CAN/CAN.h"
#include "IoT/CAN/CANFrame.h"
#include "IoT/CAN/CANFDFrame.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Array.h"
#include <vector>


namespace IoT {
namespace CAN {


//@ serialize
struct Filter
	/// A simple filter for CAN messages.
	///
	/// A filter matches if received_id && mask == id && mask.
	///
	/// The filter condition can be inverted by setting the invert flag to true.
{
	Filter():
		id(0),
		mask(0),
		invert(false)
	{
	}

	Poco::UInt32 id;
		/// 11-bit or 29-bit CAN ID

	Poco::UInt32 mask;
		/// Mask for CAN ID

	//@ optional
	bool invert;
		/// Invert filter condition
};


//@ remote
class IoTCAN_API CANEndpoint
	/// The CANEndpoint is used to receive and send CAN and CAN-FD frames.
{
public:
	typedef Poco::SharedPtr<CANEndpoint> Ptr;

	Poco::BasicEvent<const CANFrame> frameReceived;
		/// Fired when an CAN frame has been received.

	Poco::BasicEvent<const CANFDFrame> fdFrameReceived;
		/// Fired when an CAN-FD frame has been received.

	CANEndpoint();
		/// Creates the CANEndpoint.

	virtual ~CANEndpoint();
		/// Destroys the CANEndpoint.

	virtual std::string device() const = 0;
		/// Returns the interface device name (e.g., "can0").

	virtual void setFilter(const std::vector<Filter>& filter) = 0;
		/// Sets a frame filter for CAN messages.

	virtual std::vector<Filter> getFilter() const = 0;
		/// Returns the current filter.

	virtual bool addFilter(const Filter& filter) = 0;
		/// Adds a filter element to the frame filter.

	virtual bool removeFilter(const Filter& filter) = 0;
		/// Removes the given filter element.

	virtual void sendFrame(const CANFrame& frame) = 0;
		/// Transmits the given CAN frame.

	virtual void sendFDFrame(const CANFDFrame& frame) = 0;
		/// Transmits the given CAN-FD frame.

	virtual void enableEvents(bool enable = true) = 0;
		/// Enables or disables events for received frames.

	virtual bool eventsEnabled() const = 0;
		/// Returns true if events for received frames are enabled, otherwise false.
};


} } // namespace IoT::CAN


#endif // IoT_CAN_CANEndpoint_INCLUDED
