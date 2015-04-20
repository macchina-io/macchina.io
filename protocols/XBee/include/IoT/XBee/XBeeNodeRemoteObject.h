//
// XBeeNodeRemoteObject.h
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNodeRemoteObject_INCLUDED
#define IoT_XBee_XBeeNodeRemoteObject_INCLUDED


#include "IoT/XBee/IXBeeNode.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XBee {


class XBeeNodeRemoteObject: public IoT::XBee::IXBeeNode, public Poco::RemotingNG::RemoteObject
	/// This class provides a high-level interface to a Digi XBee device
	/// using the Digi XBee API frame-based protocol.
{
public:
	typedef Poco::AutoPtr<XBeeNodeRemoteObject> Ptr;

	XBeeNodeRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject);
		/// Creates a XBeeNodeRemoteObject.

	virtual ~XBeeNodeRemoteObject();
		/// Destroys the XBeeNodeRemoteObject.

	virtual void queueCommand(const IoT::XBee::ATCommand& command);
		/// Queues an AT command for execution on the connected XBee device.
		///
		/// In contrast to sendATCommand(), new parameter values are queued 
		/// and not applied until either sendATCommand() is called
		/// or the Apply Changes (AC) AT command is issued. Register queries 
		/// (reading parameter values) are returned immediately.

	virtual void remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void sendCommand(const IoT::XBee::ATCommand& command);
		/// Sends an AT command to the connected XBee device.

	virtual void sendFrame(const IoT::XBee::APIFrame& frame);
		/// Sends an API frame to the connected XBee device.

	virtual void sendRemoteCommand(const IoT::XBee::RemoteATCommand& command);
		/// Sends an AT command to a remote XBee device.

protected:
	void event__commandResponseReceived(const IoT::XBee::ATCommandResponse& data);

	void event__frameReceived(const IoT::XBee::APIFrame& data);

	void event__ioSampleReceived(const IoT::XBee::IOSample& data);

	void event__remoteCommandResponseReceived(const IoT::XBee::RemoteATCommandResponse& data);

private:
	Poco::SharedPtr<IoT::XBee::XBeeNode> _pServiceObject;
};


inline void XBeeNodeRemoteObject::queueCommand(const IoT::XBee::ATCommand& command)
{
	_pServiceObject->queueCommand(command);
}


inline const Poco::RemotingNG::Identifiable::TypeId& XBeeNodeRemoteObject::remoting__typeId() const
{
	return IXBeeNode::remoting__typeId();
}


inline void XBeeNodeRemoteObject::sendCommand(const IoT::XBee::ATCommand& command)
{
	_pServiceObject->sendCommand(command);
}


inline void XBeeNodeRemoteObject::sendFrame(const IoT::XBee::APIFrame& frame)
{
	_pServiceObject->sendFrame(frame);
}


inline void XBeeNodeRemoteObject::sendRemoteCommand(const IoT::XBee::RemoteATCommand& command)
{
	_pServiceObject->sendRemoteCommand(command);
}


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_XBeeNodeRemoteObject_INCLUDED

