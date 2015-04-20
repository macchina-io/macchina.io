//
// XBeeNodeEventDispatcher.h
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNodeEventDispatcher_INCLUDED
#define IoT_XBee_XBeeNodeEventDispatcher_INCLUDED


#include "IoT/XBee/XBeeNodeRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace XBee {


class XBeeNodeEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// This class provides a high-level interface to a Digi XBee device
	/// using the Digi XBee API frame-based protocol.
{
public:
	XBeeNodeEventDispatcher(XBeeNodeRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a XBeeNodeEventDispatcher.

	virtual ~XBeeNodeEventDispatcher();
		/// Destroys the XBeeNodeEventDispatcher.

	void event__commandResponseReceived(const void* pSender, const IoT::XBee::ATCommandResponse& data);

	void event__frameReceived(const void* pSender, const IoT::XBee::APIFrame& data);

	void event__ioSampleReceived(const void* pSender, const IoT::XBee::IOSample& data);

	void event__remoteCommandResponseReceived(const void* pSender, const IoT::XBee::RemoteATCommandResponse& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__commandResponseReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ATCommandResponse& data);

	void event__frameReceivedImpl(const std::string& subscriberURI, const IoT::XBee::APIFrame& data);

	void event__ioSampleReceivedImpl(const std::string& subscriberURI, const IoT::XBee::IOSample& data);

	void event__remoteCommandResponseReceivedImpl(const std::string& subscriberURI, const IoT::XBee::RemoteATCommandResponse& data);

	static const std::string DEFAULT_NS;
	XBeeNodeRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& XBeeNodeEventDispatcher::remoting__typeId() const
{
	return IXBeeNode::remoting__typeId();
}


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_XBeeNodeEventDispatcher_INCLUDED

