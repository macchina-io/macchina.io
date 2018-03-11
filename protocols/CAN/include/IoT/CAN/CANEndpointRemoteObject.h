//
// CANEndpointRemoteObject.h
//
// Library: IoT/CAN
// Package: Generated
// Module:  CANEndpointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_CANEndpointRemoteObject_INCLUDED
#define IoT_CAN_CANEndpointRemoteObject_INCLUDED


#include "IoT/CAN/ICANEndpoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CAN {


class CANEndpointRemoteObject: public IoT::CAN::ICANEndpoint, public Poco::RemotingNG::RemoteObject
	/// The CANEndpoint is used to receive and send CAN and CAN-FD frames.
{
public:
	typedef Poco::AutoPtr<CANEndpointRemoteObject> Ptr;

	CANEndpointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject);
		/// Creates a CANEndpointRemoteObject.

	virtual ~CANEndpointRemoteObject();
		/// Destroys the CANEndpointRemoteObject.

	virtual bool addFilter(const IoT::CAN::Filter& filter);
		/// Adds a filter element to the frame filter.
		///
		/// Returns true if the filter was added, or false
		/// if the filter was already present.

	virtual std::string device() const;
		/// Returns the interface device name (e.g., "can0").

	virtual void enableEvents(bool enable = bool(true));
		/// Enables or disables events for received CAN frames.

	virtual void enableFDEvents(bool enable = bool(true));
		/// Enables or disables events for received CAN-FD frames.

	virtual bool eventsEnabled() const;
		/// Returns true if events for received CAN frames are enabled, otherwise false.

	virtual bool fdEventsEnabled() const;
		/// Returns true if events for received CAN-FD frames are enabled, otherwise false.

	virtual bool fdFramesSupported() const;
		/// Returns true if the implementation supports CAN-FD.

	std::vector < IoT::CAN::Filter > getFilter() const;
		/// Returns the current filter.

	IoT::CAN::FilterMode getFilterMode() const;
		/// Returns the filter mode.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual bool removeFilter(const IoT::CAN::Filter& filter);
		/// Removes the given filter element.
		///
		/// Returns true if the filter was removed, or false
		/// if no such filter was set.

	virtual void sendCANFDFrame(const IoT::CAN::CANFDFrame& frame);
		/// Transmits the given CAN-FD frame.

	virtual void sendCANFrame(const IoT::CAN::CANFrame& frame);
		/// Transmits the given CAN frame.

	virtual void sendFrame(const IoT::CAN::CANFDFrame& frame, IoT::CAN::FrameType type = IoT::CAN::FrameType(IoT::CAN::CAN_FRAME_AUTO));
		/// Transmit the given frame as CAN or CAN-FD frame, depending
		/// on type.

	virtual void setFilter(const std::vector < IoT::CAN::Filter >& filter);
		/// Sets a frame filter for CAN messages.

	virtual void setFilterMode(IoT::CAN::FilterMode mode);
		/// Sets the filter mode (defaults to CAN_FILTER_MODE_OR).

protected:
	void event__fdFrameReceived(const IoT::CAN::CANFDFrame& data);

	void event__frameReceived(const IoT::CAN::CANFrame& data);

private:
	Poco::SharedPtr<IoT::CAN::CANEndpoint> _pServiceObject;
};


inline bool CANEndpointRemoteObject::addFilter(const IoT::CAN::Filter& filter)
{
	return _pServiceObject->addFilter(filter);
}


inline std::string CANEndpointRemoteObject::device() const
{
	return _pServiceObject->device();
}


inline void CANEndpointRemoteObject::enableEvents(bool enable)
{
	_pServiceObject->enableEvents(enable);
}


inline void CANEndpointRemoteObject::enableFDEvents(bool enable)
{
	_pServiceObject->enableFDEvents(enable);
}


inline bool CANEndpointRemoteObject::eventsEnabled() const
{
	return _pServiceObject->eventsEnabled();
}


inline bool CANEndpointRemoteObject::fdEventsEnabled() const
{
	return _pServiceObject->fdEventsEnabled();
}


inline bool CANEndpointRemoteObject::fdFramesSupported() const
{
	return _pServiceObject->fdFramesSupported();
}


inline std::vector < IoT::CAN::Filter > CANEndpointRemoteObject::getFilter() const
{
	return _pServiceObject->getFilter();
}


inline IoT::CAN::FilterMode CANEndpointRemoteObject::getFilterMode() const
{
	return _pServiceObject->getFilterMode();
}


inline const Poco::RemotingNG::Identifiable::TypeId& CANEndpointRemoteObject::remoting__typeId() const
{
	return ICANEndpoint::remoting__typeId();
}


inline bool CANEndpointRemoteObject::removeFilter(const IoT::CAN::Filter& filter)
{
	return _pServiceObject->removeFilter(filter);
}


inline void CANEndpointRemoteObject::sendCANFDFrame(const IoT::CAN::CANFDFrame& frame)
{
	_pServiceObject->sendCANFDFrame(frame);
}


inline void CANEndpointRemoteObject::sendCANFrame(const IoT::CAN::CANFrame& frame)
{
	_pServiceObject->sendCANFrame(frame);
}


inline void CANEndpointRemoteObject::sendFrame(const IoT::CAN::CANFDFrame& frame, IoT::CAN::FrameType type)
{
	_pServiceObject->sendFrame(frame, type);
}


inline void CANEndpointRemoteObject::setFilter(const std::vector < IoT::CAN::Filter >& filter)
{
	_pServiceObject->setFilter(filter);
}


inline void CANEndpointRemoteObject::setFilterMode(IoT::CAN::FilterMode mode)
{
	_pServiceObject->setFilterMode(mode);
}


} // namespace CAN
} // namespace IoT


#endif // IoT_CAN_CANEndpointRemoteObject_INCLUDED

