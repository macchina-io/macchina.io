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
	/// using the Digi XBee API frame-based protocol. This class can be
	/// used with all XBee devices supporting the XBee API frame-based
	/// protocol, including ZigBee devices. Actually supported methods
	/// and events are depending on the kind of XBee device, e.g., an
	/// 802.15.4 module won't support ZigBee-specific API frames, and
	/// vice-versa. Please refer to the XBee product manual for detailed
	/// information about the API.
{
public:
	XBeeNodeEventDispatcher(XBeeNodeRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a XBeeNodeEventDispatcher.

	virtual ~XBeeNodeEventDispatcher();
		/// Destroys the XBeeNodeEventDispatcher.

	void event__commandResponseReceived(const void* pSender, const IoT::XBee::ATCommandResponse& data);

	void event__explicitAddressingZigBeePacketReceived(const void* pSender, const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data);

	void event__frameReceived(const void* pSender, const IoT::XBee::APIFrame& data);

	void event__ioDataReceived(const void* pSender, const IoT::XBee::ReceivePacket& data);

	void event__ioSampleReceived(const void* pSender, const IoT::XBee::IOSample& data);

	void event__modemStatusReceived(const void* pSender, const IoT::XBee::ModemStatus& data);

	void event__packetReceived(const void* pSender, const IoT::XBee::ReceivePacket& data);

	void event__remoteCommandResponseReceived(const void* pSender, const IoT::XBee::RemoteATCommandResponse& data);

	void event__sensorReadReceived(const void* pSender, const IoT::XBee::SensorRead& data);

	void event__transmitStatusReceived(const void* pSender, const IoT::XBee::TransmitStatus& data);

	void event__zigBeePacketReceived(const void* pSender, const IoT::XBee::ZigBeeReceivePacket& data);

	void event__zigBeeTransmitStatusReceived(const void* pSender, const IoT::XBee::ZigBeeTransmitStatus& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__commandResponseReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ATCommandResponse& data);

	void event__explicitAddressingZigBeePacketReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data);

	void event__frameReceivedImpl(const std::string& subscriberURI, const IoT::XBee::APIFrame& data);

	void event__ioDataReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ReceivePacket& data);

	void event__ioSampleReceivedImpl(const std::string& subscriberURI, const IoT::XBee::IOSample& data);

	void event__modemStatusReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ModemStatus& data);

	void event__packetReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ReceivePacket& data);

	void event__remoteCommandResponseReceivedImpl(const std::string& subscriberURI, const IoT::XBee::RemoteATCommandResponse& data);

	void event__sensorReadReceivedImpl(const std::string& subscriberURI, const IoT::XBee::SensorRead& data);

	void event__transmitStatusReceivedImpl(const std::string& subscriberURI, const IoT::XBee::TransmitStatus& data);

	void event__zigBeePacketReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ZigBeeReceivePacket& data);

	void event__zigBeeTransmitStatusReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ZigBeeTransmitStatus& data);

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

