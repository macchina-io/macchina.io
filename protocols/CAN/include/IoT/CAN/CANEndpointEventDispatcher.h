//
// CANEndpointEventDispatcher.h
//
// Library: IoT/CAN
// Package: Generated
// Module:  CANEndpointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_CANEndpointEventDispatcher_INCLUDED
#define IoT_CAN_CANEndpointEventDispatcher_INCLUDED


#include "IoT/CAN/CANEndpointRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace CAN {


class CANEndpointEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The CANEndpoint is used to receive and send CAN and CAN-FD frames.
{
public:
	CANEndpointEventDispatcher(CANEndpointRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a CANEndpointEventDispatcher.

	virtual ~CANEndpointEventDispatcher();
		/// Destroys the CANEndpointEventDispatcher.

	void event__frameReceived(const void* pSender, const IoT::CAN::CANFDFrame& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__frameReceivedImpl(const std::string& subscriberURI, const IoT::CAN::CANFDFrame& data);

	static const std::string DEFAULT_NS;
	CANEndpointRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CANEndpointEventDispatcher::remoting__typeId() const
{
	return ICANEndpoint::remoting__typeId();
}


} // namespace CAN
} // namespace IoT


#endif // IoT_CAN_CANEndpointEventDispatcher_INCLUDED

