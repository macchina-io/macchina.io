//
// ICANEndpoint.h
//
// Library: IoT/CAN
// Package: Generated
// Module:  ICANEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_ICANEndpoint_INCLUDED
#define IoT_CAN_ICANEndpoint_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace CAN {


class ICANEndpoint: public Poco::OSP::Service
	/// The CANEndpoint is used to receive and send CAN and CAN-FD frames.
{
public:
	using Ptr = Poco::AutoPtr<ICANEndpoint>;

	ICANEndpoint();
		/// Creates a ICANEndpoint.

	virtual ~ICANEndpoint();
		/// Destroys the ICANEndpoint.

	virtual bool addFilter(const IoT::CAN::Filter& filter) = 0;
		/// Adds a filter element to the frame filter.
		///
		/// Returns true if the filter was added, or false
		/// if the filter was already present.

	virtual std::string device() const = 0;
		/// Returns the interface device name (e.g., "can0").

	virtual void enableEvents(bool enable = bool(true)) = 0;
		/// Enables or disables events for received CAN frames.

	virtual void enableFD(bool enable = bool(true)) = 0;
		/// Enables or disables support for CAN-FD frames.

	virtual bool eventsEnabled() const = 0;
		/// Returns true if events for received CAN frames are enabled, otherwise false.

	virtual bool fdEnabled() const = 0;
		/// Returns true if CAN-FD frames are enabled, otherwise false.

	virtual bool fdSupported() const = 0;
		/// Returns true if the implementation supports CAN-FD, otherwise false.

	virtual std::vector<IoT::CAN::Filter> getFilter() const = 0;
		/// Returns the current filter.

	virtual IoT::CAN::FilterMode getFilterMode() const = 0;
		/// Returns the filter mode.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

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

	virtual bool removeFilter(const IoT::CAN::Filter& filter) = 0;
		/// Removes the given filter element.
		///
		/// Returns true if the filter was removed, or false
		/// if no such filter was set.

	virtual void sendCANFDFrame(const IoT::CAN::CANFDFrame& frame) = 0;
		/// Transmits the given CAN-FD frame.

	virtual void sendCANFrame(const IoT::CAN::CANFrame& frame) = 0;
		/// Transmits the given CAN frame.

	virtual void sendFrame(const IoT::CAN::CANFDFrame& frame, IoT::CAN::FrameType type = IoT::CAN::FrameType(IoT::CAN::CAN_FRAME_AUTO)) = 0;
		/// Transmit the given frame as CAN or CAN-FD frame, depending
		/// on type.

	virtual void setFilter(const std::vector<IoT::CAN::Filter>& filter) = 0;
		/// Sets a frame filter for CAN messages.

	virtual void setFilterMode(IoT::CAN::FilterMode mode) = 0;
		/// Sets the filter mode (defaults to CAN_FILTER_MODE_OR).

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent<const IoT::CAN::CANFDFrame> frameReceived;
};


} // namespace CAN
} // namespace IoT


#endif // IoT_CAN_ICANEndpoint_INCLUDED

