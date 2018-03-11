//
// CANEndpoint.h
//
// Library: IoT/CAN
// Package: CANEndpoint
// Module:  CANEndpoint
//
// Definition of the CANEndpoint interface.
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
	enum
	{
		CAN_FILTER_MASK_SFF = 0x000007FFU, /// Standard Frame Format mask
		CAN_FILTER_MASK_EFF = 0x1FFFFFFFU, /// Extended Frame Format mask
		CAN_FILTER_FLAG_RTR = 0x40000000U, /// RTR Flag for ID and/or mask
		CAN_FILTER_FLAG_EFF = 0x80000000U  /// Extended Frame Flag for ID and/or mask
	};

	Filter():
		id(0),
		mask(0),
		invert(false)
	{
	}

	Poco::UInt32 id;
		/// 11-bit or 29-bit CAN ID. For a 29-bit ID must be or-ed with CAN_FILTER_FLAG_EFF.

	Poco::UInt32 mask;
		/// Mask for CAN ID (CAN_FILTER_MASK_SFF, CAN_FILTER_MASK_EFF, CAN_FILTER_MASK_RTR, or custom).

	//@ optional
	bool invert;
		/// Invert filter condition.
};


enum FilterMode
	/// Filter modes for setFilterMode()/getFilterMode()
{
	CAN_FILTER_MODE_OR  = 0, /// Frame passes if it matches at least one filter element (default)
	CAN_FILTER_MODE_AND = 1  /// Frame passes if it matches all filter elements
};


enum FrameType
	/// Frame type for sendAnyFrame()
{
	CAN_FRAME_AUTO  = 0, /// Send frame as CAN or CAN-FD frame, depending on payload length
	CAN_FRAME_CAN   = 1, /// Send frame as standard CAN frame
	CAN_FRAME_CANFD = 2  /// Send frame as CAN-FD frame
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
		///
		/// Returns true if the filter was added, or false
		/// if the filter was already present.

	virtual bool removeFilter(const Filter& filter) = 0;
		/// Removes the given filter element.
		///
		/// Returns true if the filter was removed, or false
		/// if no such filter was set.

	virtual void setFilterMode(FilterMode mode) = 0;
		/// Sets the filter mode (defaults to CAN_FILTER_MODE_OR).

	virtual FilterMode getFilterMode() const = 0;
		/// Returns the filter mode.

	virtual void sendCANFrame(const CANFrame& frame) = 0;
		/// Transmits the given CAN frame.

	virtual void sendCANFDFrame(const CANFDFrame& frame) = 0;
		/// Transmits the given CAN-FD frame.

	//@ $type={optional}
	virtual void sendFrame(const CANFDFrame& frame, FrameType type = CAN_FRAME_AUTO) = 0;
		/// Transmit the given frame as CAN or CAN-FD frame, depending
		/// on type.

	//@ $enable={optional}
	virtual void enableEvents(bool enable = true) = 0;
		/// Enables or disables events for received CAN frames.

	virtual bool eventsEnabled() const = 0;
		/// Returns true if events for received CAN frames are enabled, otherwise false.

	//@ $enable={optional}
	virtual void enableFDEvents(bool enable = true) = 0;
		/// Enables or disables events for received CAN-FD frames.

	virtual bool fdEventsEnabled() const = 0;
		/// Returns true if events for received CAN-FD frames are enabled, otherwise false.

	virtual bool fdFramesSupported() const = 0;
		/// Returns true if the implementation supports CAN-FD.
};


} } // namespace IoT::CAN


#endif // IoT_CAN_CANEndpoint_INCLUDED
