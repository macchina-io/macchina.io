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
	/// using the Digi XBee API frame-based protocol. This class can be
	/// used with all XBee devices supporting the XBee API frame-based
	/// protocol, including ZigBee devices. Actually supported methods
	/// and events are depending on the kind of XBee device, e.g., an
	/// 802.15.4 module won't support ZigBee-specific API frames, and
	/// vice-versa. Please refer to the XBee product manual for detailed
	/// information about the API.
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
		/// In contrast to sendCommand(), new parameter values are queued 
		/// and not applied until either sendCommand() is called
		/// or the Apply Changes (AC) AT command is issued. Register queries 
		/// (reading parameter values) are returned immediately.

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

	virtual void sendCommand(const IoT::XBee::ATCommand& command) = 0;
		/// Sends an AT command to the connected XBee device.

	virtual void sendExplicitAddressingZigBeeTransmitRequest(const IoT::XBee::ExplicitAddressingZigBeeTransmitRequest& request) = 0;
		/// Sends an ExplicitAddressingZigBeeTransmitRequest to the XBee device.

	virtual void sendFrame(const IoT::XBee::APIFrame& frame) = 0;
		/// Sends an API frame to the connected XBee device.
		///
		/// The caller is responsible for correct formatting of the
		/// API frame's data. Refer to the XBee module documentation for
		/// supported frames and their format.
		///
		/// This can be used to send API frames not directly supported
		/// by the XBeeNode interface.

	virtual void sendRemoteCommand(const IoT::XBee::RemoteATCommand& command) = 0;
		/// Sends an AT command to a remote XBee device.

	virtual void sendTransmitRequest(const IoT::XBee::TransmitRequest& request) = 0;
		/// Sends a TransmitRequest message to the XBee device.

	virtual void sendZigBeeTransmitRequest(const IoT::XBee::ZigBeeTransmitRequest& request) = 0;
		/// Sends a ZigBeeTransmitRequest to the XBee device.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const ATCommandResponse > commandResponseReceived;
	Poco::BasicEvent < const ExplicitAddressingZigBeeReceivePacket > explicitAddressingZigBeePacketReceived;
	Poco::BasicEvent < const APIFrame > frameReceived;
	Poco::BasicEvent < const ReceivePacket > ioDataReceived;
	Poco::BasicEvent < const IOSample > ioSampleReceived;
	Poco::BasicEvent < const ModemStatus > modemStatusReceived;
	Poco::BasicEvent < const ReceivePacket > packetReceived;
	Poco::BasicEvent < const RemoteATCommandResponse > remoteCommandResponseReceived;
	Poco::BasicEvent < const SensorRead > sensorReadReceived;
	Poco::BasicEvent < const TransmitStatus > transmitStatusReceived;
	Poco::BasicEvent < const ZigBeeReceivePacket > zigBeePacketReceived;
	Poco::BasicEvent < const ZigBeeTransmitStatus > zigBeeTransmitStatusReceived;
};


} // namespace XBee
} // namespace IoT


#endif // IoT_XBee_IXBeeNode_INCLUDED

