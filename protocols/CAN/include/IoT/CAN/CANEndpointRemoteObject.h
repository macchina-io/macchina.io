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

	virtual std::string device() const;
		/// Returns the interface device name (e.g., "can0").

	virtual void enableEvents(bool enable = bool(true));
		/// Enables or disables events for received frames.

	virtual bool eventsEnabled() const;
		/// Returns true if events for received frames are enabled, otherwise false.

	std::vector < IoT::CAN::Filter > getFilter() const;
		/// Returns the current filter.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual bool removeFilter(const IoT::CAN::Filter& filter);
		/// Removes the given filter element.

	virtual void sendFDFrame(const IoT::CAN::CANFDFrame& frame);
		/// Transmits the given CAN-FD frame.

	virtual void sendFrame(const IoT::CAN::CANFrame& frame);
		/// Transmits the given CAN frame.

	virtual void setFilter(const std::vector < IoT::CAN::Filter >& filter);
		/// Sets a frame filter for CAN messages.

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


inline bool CANEndpointRemoteObject::eventsEnabled() const
{
	return _pServiceObject->eventsEnabled();
}


inline std::vector < IoT::CAN::Filter > CANEndpointRemoteObject::getFilter() const
{
	return _pServiceObject->getFilter();
}


inline const Poco::RemotingNG::Identifiable::TypeId& CANEndpointRemoteObject::remoting__typeId() const
{
	return ICANEndpoint::remoting__typeId();
}


inline bool CANEndpointRemoteObject::removeFilter(const IoT::CAN::Filter& filter)
{
	return _pServiceObject->removeFilter(filter);
}


inline void CANEndpointRemoteObject::sendFDFrame(const IoT::CAN::CANFDFrame& frame)
{
	_pServiceObject->sendFDFrame(frame);
}


inline void CANEndpointRemoteObject::sendFrame(const IoT::CAN::CANFrame& frame)
{
	_pServiceObject->sendFrame(frame);
}


inline void CANEndpointRemoteObject::setFilter(const std::vector < IoT::CAN::Filter >& filter)
{
	_pServiceObject->setFilter(filter);
}


} // namespace CAN
} // namespace IoT


#endif // IoT_CAN_CANEndpointRemoteObject_INCLUDED

