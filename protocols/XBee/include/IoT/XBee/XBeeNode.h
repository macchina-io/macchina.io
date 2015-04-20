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
	/// A Raw XBee API frame.
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
struct ATCommand
	/// An AT command sent to the connected XBee module.
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
{
	Poco::UInt8 frameID;
		/// Correlates response frame with command frame.
		
	std::string command;
		/// Two character AT command.
		
	Poco::UInt8 status;
		/// Command status;
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
		/// Bitfield of supported transmission options. 
		/// Supported values include the following: 
		///   - 0x01 - Disable retries and route repair
		///   - 0x02 - Apply changes
		///   - 0x20 - Enable APS encryption (if EE=1)
		///   - 0x40 - Use the extended transmission timeout
		///
		/// If apply changes is not enabled, then an AC command must be sent before 
		/// changes will take effect.
		/// Enabling APS encryption presumes the source and destination have been 
		/// authenticated. It also decreases the maximum number of RF payload bytes by 
		/// 4 (below the value reported by NP).
		/// The extended transmission timeout is needed when addressing sleeping end 
		/// devices. It increases the retry interval between retries to com

	std::string command; 
		/// Two character AT command.

	std::vector<Poco::UInt8> parameters;
		/// Command-specific parameter bytes.
};


//@ serialize
struct RemoteATCommandResponse
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
		/// Command status;
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
	/// ZigBee IO Data Sample Rx Indicator
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


//@ remote
class IoTXBee_API XBeeNode
	/// This class provides a high-level interface to a Digi XBee device
	/// using the Digi XBee API frame-based protocol.
{
public:
	Poco::BasicEvent<const APIFrame> frameReceived;
		/// Fired when a valid frame has been received from the connected XBee device.

	Poco::BasicEvent<const ATCommandResponse> commandResponseReceived;
		/// Fired when an AT command response frame has been received from 
		/// the connected XBee device.
	
	Poco::BasicEvent<const RemoteATCommandResponse> remoteCommandResponseReceived;
		/// Fired when an AT command response frame has been received from 
		/// the connected XBee device.
		
	Poco::BasicEvent<const IOSample> ioSampleReceived;
		/// Fired when an ZigBee IO Data Sample Rx Indicator frame has been received from
		/// the connected XBee device.
	
	XBeeNode();
		/// Creates a XBeeNode.
		
	virtual ~XBeeNode();
		/// Destroys the ZBPort.

	virtual void sendFrame(const APIFrame& frame) = 0;
		/// Sends an API frame to the connected XBee device.

	virtual void sendCommand(const ATCommand& command) = 0;
		/// Sends an AT command to the connected XBee device.
		
	virtual void queueCommand(const ATCommand& command) = 0;
		/// Queues an AT command for execution on the connected XBee device.
		///
		/// In contrast to sendATCommand(), new parameter values are queued 
		/// and not applied until either sendATCommand() is called
		/// or the Apply Changes (AC) AT command is issued. Register queries 
		/// (reading parameter values) are returned immediately.

	virtual void sendRemoteCommand(const RemoteATCommand& command) = 0;
		/// Sends an AT command to a remote XBee device.

private:
	XBeeNode(const XBeeNode&);
	XBeeNode& operator = (const XBeeNode&);
};


} } // namespace IoT::XBee


#endif // IoT_XBee_XBeeNode_INCLUDED
