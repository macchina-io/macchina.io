//
// XBeeNode.h
//
// $Id$
//
// Library: IoT/XBee
// Package: XBeeNode
// Module:  XBeeNode
//
// Definition of the XBeeNode class.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNode_INCLUDED
#define IoT_XBee_XBeeNode_INCLUDED


#include "IoT/XBee/XBee.h"
#include "Poco/BasicEvent.h"
#include <vector>


namespace IoT {
namespace XBee {


//@ serialize
struct APIFrame
	/// A raw XBee API frame.
	///
	/// Please refer to the XBee API or XBee ZigBee API specification
	/// for more information.
{
	Poco::UInt8 type;
		/// API frame type. See XBeeFrame::FrameType for more information.
		
	std::vector<Poco::UInt8> data;
		/// API frame data.
};


//@ serialize
struct ModemStatus
	/// Modem Status frame reported by XBee module.
	///
	/// Frame Type: 0x8A
{
	Poco::UInt8 status;
		/// Modem status.
		///   - 0x00 = Hardware reset
		///   - 0x01 = Watchdog timer reset
		///   - 0x02 = Joined network (routers and end devices)
		///   - 0x03 = Disassociated
		///   - 0x06 = Coordinator started
		///   - 0x07 = Network security key was updated
		///   - 0x0D = Voltage supply limit exceeded
		///   - 0x11 = Modem configuration changed while join in progress
		///   - 0x80+ = Stack error
};


//@ serialize
struct TransmitRequest
	/// A TX Request message will cause the module to transmit data as an RF Packet.
	///
	/// Frame Type: 0x00 or 0x01
{
	Poco::UInt8 frameID;
		/// Identifies the serial port data frame for the host to correlate 
		/// with a subsequent ACK (acknowledgement). If set to 0, no response is sent.
	
	std::string deviceOrNetworkAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device.
		/// Can be "000000000000FFFF" for broadcast. Alternatively, the 16-bit network
		/// address can also be specified, which can be "FFFF" for broadcast.
	
	Poco::UInt8 options;
		/// Option flags.
		///   - 0x01 = Disable ACK
		///   - 0x04 = Send packet with Broadcast Pan ID
		///
		/// All other bits must be set to 0.
		
	std::vector<Poco::UInt8> payload;
		/// Up to 100 bytes of payload.
};


//@ serialize
struct TransmitStatus
	/// When a TX Request is completed, the module sends a TX Status message. 
	/// This message will indicate if the packet was transmitted successfully or if there was a failure.
	///
	/// Frame Type: 0x89
{
	Poco::UInt8 frameID;
		/// Identifies UART data frame being reported.
		
	Poco::UInt8 status;
		/// Status byte:
		///   - 0 = Success
		///   - 1 = No ACK (Acknowledgement) received
		///   - 2 = CCA failure
		///   - 3 = Purged
};


//@ serialize
struct ReceivePacket
	/// When the module receives an RF packet, it is sent out the UART using this message type.
	///
	/// Frame Type: 0x80, 0x81, 0x82 or 0x83
{
	std::string deviceOrNetworkAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device,
		/// or 16-bit network address.

	Poco::UInt8 rssi;
		/// Received Signal Strength Indicator - Hexadecimal equivalent of (-dBm) value. 
		/// For example: If RX signal strength = -40 dBm, “0x28” (40 decimal) is returned.
	
	Poco::UInt8 options;
		/// Option flags:
		///   - bit 0 [reserved]
		///   - bit 1 = Address broadcast 
		///   - bit 2 = PAN broadcast 
		///   - bits 3-7 [reserved]
	
	std::vector<Poco::UInt8> payload;
		/// Up to 100 bytes of payload.
};


//@ serialize
struct ZigBeeTransmitRequest
	/// A Transmit Request API frame causes the module to send data as an RF packet 
	/// to the specified destination.
	///
	/// Frame Type: 0x10
{
	Poco::UInt8 frameID;
		/// Identifies the serial port data frame for the host to correlate 
		/// with a subsequent ACK (acknowledgement). If set to 0, no response is sent.

	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device.
		/// Can be "0000000000000000" or empty for the coordinator, or "000000000000FFFF"
		/// for broadcast.
		
	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the device.
		/// Can be left empty or set to "FFFE" if the address is unknown, or if sending 
		/// a broadcast.
		
	Poco::UInt8 broadcastRadius;
		/// Sets maximum number of hops a broadcast transmission can occur. 
		/// If set to 0, the broadcast radius will be set to the maximum hops value.

	Poco::UInt8 options;
		/// Bitfield of supported transmission options. 
		/// Supported values include the following:
		///   - 0x01 - Disable retries
		///   - 0x20 - Enable APS encryption (if EE=1)
		///   - 0x40 - Use the extended transmission timeout for this destination
		/// 
		/// Enabling APS encryption decreases the maximum number of RF payload 
		/// bytes by 4 (below the value reported by NP).
		/// Setting the extended timeout bit causes the stack to set the extended 
		/// transmission timeout for the destination address.
		/// All unused and unsupported bits must be set to 0.
		
	std::vector<Poco::UInt8> payload;
		/// Data that is sent to the destination device.
};


//@ serialize
struct ExplicitAddressingZigBeeTransmitRequest
	/// Allows ZigBee application layer fields (endpoint and cluster ID) to be 
	/// specified for a data transmission.
	/// 
	/// Similar to the ZigBee Transmit Request, but also requires ZigBee application 
	/// layer addressing fields to be specified (endpoints, cluster ID, profile ID). 
	/// An Explicit Addressing Request API frame causes the module to send data as an 
	/// RF packet to the specified destination, using the specified source and destination 
	/// endpoints, cluster ID, and profile ID.
	///
	/// Frame Type: 0x11	
{
	Poco::UInt8 frameID;
		/// Identifies the serial port data frame for the host to correlate 
		/// with a subsequent ACK (acknowledgement). If set to 0, no response is sent.

	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device.
		/// Can be "0000000000000000" or empty for the coordinator, or "000000000000FFFF"
		/// for broadcast.
		
	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the device.
		/// Can be left empty or set to "FFFE" if the address is unknown, or if sending 
		/// a broadcast.
		
	Poco::UInt8 sourceEndpoint;
		/// Source endpoint for the transmission.
	
	Poco::UInt8 destinationEndpoint;
		/// Destination endpoint for the transmission.
	
	Poco::UInt16 clusterID;
		/// Cluster ID used in the transmission
		
	Poco::UInt16 profileID;
		/// Profile ID used in the transmission.
		
	Poco::UInt8 broadcastRadius;
		/// Sets maximum number of hops a broadcast transmission can occur. 
		/// If set to 0, the broadcast radius will be set to the maximum hops value.

	Poco::UInt8 options;
		/// Bitfield of supported transmission options. 
		/// Supported values include the following:
		///   - 0x01 - Disable retries
		///   - 0x04 - Indirect addressing
		///   - 0x08 - Multicast addressing
		///   - 0x20 - Enable APS encryption (if EE=1)
		///   - 0x40 - Use the extended transmission timeout for this destination
		/// 
		/// Enabling APS encryption decreases the maximum number of RF payload 
		/// bytes by 4 (below the value reported by NP).
		/// Setting the extended timeout bit causes the stack to set the extended 
		/// transmission timeout for the destination address.
		/// All unused and unsupported bits must be set to 0.
		
	std::vector<Poco::UInt8> payload;
		/// Data that is sent to the destination device.
};


//@ serialize
struct ZigBeeTransmitStatus
	/// When a TX Request is completed, the module sends a TX Status message.
	/// This message will indicate if the packet was transmitted successfully or 
	/// if there was a failure.
	///
	/// Frame Type: 0x8B
{
	Poco::UInt8 frameID;
		/// Identifies the serial port data frame being reported.
		
	std::string networkAddress;
		/// 16-bit Network Address the packet was delivered to (if successful) as
		/// a hexadecimal string. 
		/// If not successful, this address will be "FFFD": Destination Address Unknown.

	Poco::UInt8 deliveryStatus;
		/// Delivery status:
		///   - 0x00 = Success
		///   - 0x01 = MAC ACK Failure
		///   - 0x02 = CCA Failure
		///   - 0x15 = Invalid destination endpoint
		///   - 0x21 = Network ACK Failure
		///   - 0x22 = Not Joined to Network
		///   - 0x23 = Self-addressed
		///   - 0x24 = Address Not Found
		///   - 0x25 = Route Not Found
		///   - 0x26 = Broadcast source failed to hear a neighbor relay the message
		///   - 0x2B = Invalid binding table index
		///   - 0x2C = Resource error lack of free buffers, timers, etc. 
		///   - 0x2D = Attempted broadcast with APS transmission 
		///   - 0x2E = Attempted unicast with APS transmission, but EE=0
		///   - 0x32 = Resource error lack of free buffers, timers, etc. 
		///   - 0x74 = Data payload too large
		///   - 0x75 = Indirect message unrequested

	Poco::UInt8 discoveryStatus;
		/// Discovery status:
		///   - 0x00 = No Discovery Overhead 0x01 = Address Discovery
		///   - 0x02 = Route Discovery
		///   - 0x03 = Address and Route
		///   - 0x40 = Extended Timeout Discovery
};


//@ serialize
struct ZigBeeReceivePacket
	/// When the module receives an RF packet, it is sent out the serial port using 
	/// this message type.
	///
	/// Frame Type: 0x90
{
	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device.
		
	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the device.

	Poco::UInt8 options;
		/// Receive options:
		///   - 0x01 - Packet Acknowledged
		///   - 0x02 - Packet was a broadcast packet
		///   - 0x20 - Packet encrypted with APS encryption
		///   - 0x40 - Packet sent with extended timeout enabled 
		/// 
		/// Note: Option values can be combined. For example, a 0x40 and a 0x01 will show as a 0x41.
		/// Other possible values 0x00, 0x21, 0x22, 0x41, 0x42, 0x60, 0x61, 0x62.
		
	std::vector<Poco::UInt8> payload;
		/// Received payload.
};


//@ serialize
struct ExplicitAddressingZigBeeReceivePacket
	/// When the modem receives a ZigBee RF packet it is sent out the serial port using 
	/// this message type.
	///
	/// Frame Type: 0x91
{
	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device.
		/// Set to "FFFFFFFFFFFFFFFF" (unknown 64-bit address) if the sender's 64-bit 
		/// address is unknown.
		
	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the device.
		
	Poco::UInt8 sourceEndpoint;
		/// Endpoint of the source that initiated the transmission.
		
	Poco::UInt8 destinationEndpoint;
		/// Endpoint of the destination the message is addressed to.
		
	Poco::UInt16 clusterID;
		/// Cluster ID the packet was addressed to.
		
	Poco::UInt16 profileID;
		/// Profile ID the packet was addressed to.

	Poco::UInt8 options;
		/// Receive options:
		///   - 0x01 - Packet Acknowledged
		///   - 0x02 - Packet was a broadcast packet
		///   - 0x20 - Packet encrypted with APS encryption
		///   - 0x40 - Packet sent with extended timeout enabled 
		/// 
		/// Note: Option values can be combined. For example, a 0x40 and a 0x01 will show as a 0x41.
		/// Other possible values 0x00, 0x21, 0x22, 0x41, 0x42, 0x60, 0x61, 0x62.
		
	std::vector<Poco::UInt8> payload;
		/// Received payload.	
};


//@ serialize
struct ATCommand
	/// An AT command sent to the connected XBee module.
	///
	/// Frame Type: 0x08
{
	Poco::UInt8 frameID; 
		/// Correlates command frame with response, if a response is required.
		/// If set to zero, no response will be sent.

	std::string command; 
		/// Two character AT command.

	std::vector<Poco::UInt8> parameters;
		/// Command-specific parameter bytes.
};


//@ serialize
struct ATCommandResponse
	/// The response to an issued AT command.
	///
	/// Frame Type: 0x88
{
	Poco::UInt8 frameID;
		/// Correlates response frame with command frame.
		
	std::string command;
		/// Two character AT command.
		
	Poco::UInt8 status;
		/// Command status:
		///   - 0 = OK
		///   - 1 = ERROR
		///   - 2 = Invalid Command 
		///   - 3 = Invalid Parameter 
		///   - 4 = Tx Failure

	std::vector<Poco::UInt8> data;
		/// Register data in binary format. If the register was set, then
		/// this field is empty.
};


//@ serialize
struct RemoteATCommand
	/// An AT command sent to a remote XBee module.
	///
	/// Frame Type: 0x17
{
	Poco::UInt8 frameID;
		/// Correlates command frame with response, if a response is required.
		/// If set to zero, no response will be sent.

	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the destination device.
		/// Can be "0000000000000000" or empty for the coordinator, or "000000000000FFFF"
		/// for broadcast.
		
	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the device.
		/// Can be left empty or set to "FFFE" if the address is unknown, or if sending 
		/// a broadcast.

	Poco::UInt8 options;
		/// Bitfield to enable various remote command options. Supported values include:
		///   - 0x01 - Disable ACK
		///   - 0x02 - Apply changes on remote. (If
		///     not set, AC command must be sent before changes will take effect.)
		///   - 0x40 - Use the extended transmission timeout for this destination.
		///
		/// Setting the extended timeout bit causes the stack to set the extended 
		/// transmission timeout for the destination address (see chapter 4).
		/// All unused and unsupported bits must be set to 0.

	std::string command; 
		/// Two character AT command.

	std::vector<Poco::UInt8> parameters;
		/// Command-specific parameter bytes.
};


//@ serialize
struct RemoteATCommandResponse
	/// The response to an issued remote AT command.
	///
	/// Frame Type: 0x97
{
	Poco::UInt8 frameID;
		/// Correlates response frame with command frame.

	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the remote device.

	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the remote device.
		
	std::string command;
		/// Two character AT command.

	Poco::UInt8 status;
		/// Command status:
		///   - 0 = OK
		///   - 1 = ERROR
		///   - 2 = Invalid Command 
		///   - 3 = Invalid Parameter 
		///   - 4 = Tx Failure

	std::vector<Poco::UInt8> data;
		/// Register data in binary format. If the register was set, then
		/// this field is empty.		
};


//@ serialize
struct IOSample
	/// ZigBee IO Data Sample Rx Indicator.
	///
	/// Frame Type: 0x92
{
	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the remote device.

	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the remote device.

	Poco::UInt8 options;
		/// Receive options:
		///   - 0x01 - Packet Acknowledged
		///   - 0x02 - Packet was a broadcast packet
		
	Poco::UInt8 nSampleSets;
		/// Number of sample sets. Always 1.
		
	Poco::UInt16 digitalChannelMask;
		/// Bitmask field that indicates which digital IO lines on the 
		/// remote have sampling enabled (if any).
		
	Poco::UInt8 analogChannelMask;
		/// Bitmask field that indicates which analog IO lines on the 
		/// remote have sampling enabled (if any).
		
	Poco::UInt16 digitalSamples;
		/// If the sample set includes any digital IO lines (digitalChannelMask > 0), 
		/// these two bytes contain samples for all enabled digital IO lines
		/// DIO lines that do not have sampling enabled return 0. 
		/// Bits in these 2 bytes map the same as they do in the digitalChannelMask field.
		
	std::vector<Poco::Int16> analogSamples;
		/// If the sample set includes any analog input lines (analogChannelMask > 0), 
		/// each enabled analog input returns a 2-byte value indicating the 
		/// A/D measurement of that input. 
		/// Analog samples are ordered sequentially from AD0/DIO0 to AD3/DIO3, 
		/// to the supply voltage.
};


//@ serialize
struct SensorRead
	/// XBee Sensor Read Indicator.
	///
	/// Frame Type: 0x94
{
	std::string deviceAddress;
		/// Hexadecimal text representation of 64-bit address of the remote device.

	std::string networkAddress;
		/// Hexadecimal text representation of the 16-bit network address of the remote device.

	Poco::UInt8 options;
		/// Receive options:
		///   - 0x01 - Packet Acknowledged
		///   - 0x02 - Packet was a broadcast packet
		
	Poco::UInt8 sensor;
		/// 1-Wire Sensors:
		///   - 0x01 = A/D Sensor Read
		///   - 0x02 = Temperature Sensor Read
		///   - 0x60 = Water present (module CD pin low)

	std::vector<Poco::Int16> analogSamples;
		/// 16-bit analog sample values from four ADCs A, B, C, D.
	
	Poco::Int16 temperature;
		/// Indicates the two-byte value read from a digital thermometer if present. 		
};


//@ remote
class IoTXBee_API XBeeNode
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
	Poco::BasicEvent<const APIFrame> frameReceived;
		/// Fired when a valid frame has been received from the connected XBee device.
		///
		/// This is fired for every receive frame. For supported frame types, a second,
		/// more specific event (transmitStatusReceived, etc.) is also fired.
		///
		/// This can be used to handle API frames not directly supported by the
		/// XBeeNode interface.
		
	Poco::BasicEvent<const TransmitStatus> transmitStatusReceived;
		/// Fired when a TX Request is completed and the module sends a TX Status message.
		
	Poco::BasicEvent<const ReceivePacket> packetReceived;
		/// Fired when a packet has been received.

	Poco::BasicEvent<const ReceivePacket> ioDataReceived;
		/// Fired when a I/O data packet has been received.

	Poco::BasicEvent<const ZigBeeTransmitStatus> zigBeeTransmitStatusReceived;
		/// Fired when a ZigBee TX Request is completed and the module sends a TX Status message.
		
	Poco::BasicEvent<const ZigBeeReceivePacket> zigBeePacketReceived;
		/// Fired when a ZigBee packet has been received.
		
	Poco::BasicEvent<const ExplicitAddressingZigBeeReceivePacket> explicitAddressingZigBeePacketReceived;
		/// Fired when an explicit addressing ZigBee packet has been received.

	Poco::BasicEvent<const ModemStatus> modemStatusReceived;
		/// Fired when a valid modem status frame has been received from the connected XBee device.

	Poco::BasicEvent<const ATCommandResponse> commandResponseReceived;
		/// Fired when an AT command response frame has been received from 
		/// the connected XBee device.
	
	Poco::BasicEvent<const RemoteATCommandResponse> remoteCommandResponseReceived;
		/// Fired when an AT command response frame has been received from 
		/// the connected XBee device.
		
	Poco::BasicEvent<const IOSample> ioSampleReceived;
		/// Fired when an ZigBee IO Data Sample Rx Indicator frame has been received from
		/// the connected XBee device.
		
	Poco::BasicEvent<const SensorRead> sensorReadReceived;
		/// Fired when a XBee Sensor Read Indicator frame has been received from the
		/// connected XBee device.
	
	XBeeNode();
		/// Creates a XBeeNode.
		
	virtual ~XBeeNode();
		/// Destroys the ZBPort.

	virtual void sendFrame(const APIFrame& frame) = 0;
		/// Sends an API frame to the connected XBee device.
		///
		/// The caller is responsible for correct formatting of the
		/// API frame's data. Refer to the XBee module documentation for
		/// supported frames and their format.
		///
		/// This can be used to send API frames not directly supported
		/// by the XBeeNode interface.

	virtual void sendCommand(const ATCommand& command) = 0;
		/// Sends an AT command to the connected XBee device.
		
	virtual void queueCommand(const ATCommand& command) = 0;
		/// Queues an AT command for execution on the connected XBee device.
		///
		/// In contrast to sendCommand(), new parameter values are queued 
		/// and not applied until either sendCommand() is called
		/// or the Apply Changes (AC) AT command is issued. Register queries 
		/// (reading parameter values) are returned immediately.

	virtual void sendRemoteCommand(const RemoteATCommand& command) = 0;
		/// Sends an AT command to a remote XBee device.
		
	virtual void sendTransmitRequest(const TransmitRequest& request) = 0;
		/// Sends a TransmitRequest message to the XBee device.
		
	virtual void sendZigBeeTransmitRequest(const ZigBeeTransmitRequest& request) = 0;
		/// Sends a ZigBeeTransmitRequest to the XBee device.
		
	virtual void sendExplicitAddressingZigBeeTransmitRequest(const ExplicitAddressingZigBeeTransmitRequest& request) = 0;
		/// Sends an ExplicitAddressingZigBeeTransmitRequest to the XBee device.

private:
	XBeeNode(const XBeeNode&);
	XBeeNode& operator = (const XBeeNode&);
};


} } // namespace IoT::XBee


#endif // IoT_XBee_XBeeNode_INCLUDED
