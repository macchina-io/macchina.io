//
// IXBeeNode.h
//
// Library: IoT/XBee
// Package: Generated
// Module:  IXBeeNode
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_IXBeeNode_INCLUDED
#define IoT_XBee_IXBeeNode_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace XBee {


class IXBeeNode: public Poco::OSP::Service
	/// This class provides a high-level interface to a Digi XBee device
	/// using the Digi XBee API frame-based protocol.
{
public:
	typedef Poco::AutoPtr<IXBeeNode> Ptr;

	IXBeeNode();
		/// Creates a IXBeeNode.

	virtual ~IXBeeNode();
		/// Destroys the IXBeeNode.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual void queueCommand(const IoT::XBee::ATCommand& command) = 0;
		/// Queues an AT command for execution on the connected XBee device.
		///
		/// In contrast to sendATCommand(), new parameter values are queued 
		/// and not applied until either sendATCommand() is called
		/// or the Apply Changes (AC) AT command is issued. Register queries 
		/// (reading parameter values) are returned immediately.

	virtual void remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void sendCommand(const IoT::XBee::ATCommand& command) = 0;
		/// Sends an AT command to the connected XBee device.

	virtual void sendFrame(const IoT::XBee::APIFrame& frame) = 0;
		/// Sends an API frame to the connected XBee device.

	virtual void sendRemoteCommand(const IoT::XBee::RemoteATCommand& command) = 0;
		/// Sends an AT command to a remote XBee device.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const ATCommandResponse > commandResponseReceived;
	Poco::BasicEvent < const APIFrame > frameReceived;
	Poco::BasicEvent < const IOSample > ioSampleReceived;
	Poco::BasicEvent < const ModemStatus > modemStatusReceived;
	Poco::BasicEvent < const RemoteATCommandResponse > remoteCommandResponseReceived;
	Poco::BasicEvent < const SensorRead > sensorReadReceived;
};


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_IXBeeNode_INCLUDED

