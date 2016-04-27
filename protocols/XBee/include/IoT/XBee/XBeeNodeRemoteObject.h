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
	/// using the Digi XBee API frame-based protocol. This class can be
	/// used with all XBee devices supporting the XBee API frame-based
	/// protocol, including ZigBee devices. Actually supported methods
	/// and events are depending on the kind of XBee device, e.g., an
	/// 802.15.4 module won't support ZigBee-specific API frames, and
	/// vice-versa. Please refer to the XBee product manual for detailed
	/// information about the API.
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
		/// In contrast to sendCommand(), new parameter values are queued 
		/// and not applied until either sendCommand() is called
		/// or the Apply Changes (AC) AT command is issued. Register queries 
		/// (reading parameter values) are returned immediately.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void sendCommand(const IoT::XBee::ATCommand& command);
		/// Sends an AT command to the connected XBee device.

	virtual void sendExplicitAddressingZigBeeTransmitRequest(const IoT::XBee::ExplicitAddressingZigBeeTransmitRequest& request);
		/// Sends an ExplicitAddressingZigBeeTransmitRequest to the XBee device.

	virtual void sendFrame(const IoT::XBee::APIFrame& frame);
		/// Sends an API frame to the connected XBee device.
		///
		/// The caller is responsible for correct formatting of the
		/// API frame's data. Refer to the XBee module documentation for
		/// supported frames and their format.
		///
		/// This can be used to send API frames not directly supported
		/// by the XBeeNode interface.

	virtual void sendRemoteCommand(const IoT::XBee::RemoteATCommand& command);
		/// Sends an AT command to a remote XBee device.

	virtual void sendTransmitRequest(const IoT::XBee::TransmitRequest& request);
		/// Sends a TransmitRequest message to the XBee device.

	virtual void sendZigBeeTransmitRequest(const IoT::XBee::ZigBeeTransmitRequest& request);
		/// Sends a ZigBeeTransmitRequest to the XBee device.

protected:
	void event__commandResponseReceived(const IoT::XBee::ATCommandResponse& data);

	void event__explicitAddressingZigBeePacketReceived(const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data);

	void event__frameReceived(const IoT::XBee::APIFrame& data);

	void event__ioDataReceived(const IoT::XBee::ReceivePacket& data);

	void event__ioSampleReceived(const IoT::XBee::IOSample& data);

	void event__modemStatusReceived(const IoT::XBee::ModemStatus& data);

	void event__packetReceived(const IoT::XBee::ReceivePacket& data);

	void event__remoteCommandResponseReceived(const IoT::XBee::RemoteATCommandResponse& data);

	void event__sensorReadReceived(const IoT::XBee::SensorRead& data);

	void event__transmitStatusReceived(const IoT::XBee::TransmitStatus& data);

	void event__zigBeePacketReceived(const IoT::XBee::ZigBeeReceivePacket& data);

	void event__zigBeeTransmitStatusReceived(const IoT::XBee::ZigBeeTransmitStatus& data);

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


inline void XBeeNodeRemoteObject::sendExplicitAddressingZigBeeTransmitRequest(const IoT::XBee::ExplicitAddressingZigBeeTransmitRequest& request)
{
	_pServiceObject->sendExplicitAddressingZigBeeTransmitRequest(request);
}


inline void XBeeNodeRemoteObject::sendFrame(const IoT::XBee::APIFrame& frame)
{
	_pServiceObject->sendFrame(frame);
}


inline void XBeeNodeRemoteObject::sendRemoteCommand(const IoT::XBee::RemoteATCommand& command)
{
	_pServiceObject->sendRemoteCommand(command);
}


inline void XBeeNodeRemoteObject::sendTransmitRequest(const IoT::XBee::TransmitRequest& request)
{
	_pServiceObject->sendTransmitRequest(request);
}


inline void XBeeNodeRemoteObject::sendZigBeeTransmitRequest(const IoT::XBee::ZigBeeTransmitRequest& request)
{
	_pServiceObject->sendZigBeeTransmitRequest(request);
}


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_XBeeNodeRemoteObject_INCLUDED

