//
// XBeeFrame.h
//
// $Id$
//
// Library: IoT/XBee
// Package: XBee
// Module:  XBeeFrame
//
// Definition of the XBeeFrame class.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeFrame_INCLUDED
#define IoT_XBee_XBeeFrame_INCLUDED


#include "IoT/XBee/XBee.h"
#include <vector>


namespace IoT {
namespace XBee {


class IoTXBee_API XBeeFrame
	/// This class encapsulates a Digi XBee API frame.
{
public:
	enum
	{
		XBEE_MAX_FRAME_LENGTH  = 1024,
		XBEE_MAX_DATA_LENGTH   = XBEE_MAX_FRAME_LENGTH - 5,
		XBEE_FRAME_START_DELIM = 0x7E
	};
	
	enum FrameType
	{
		XBEE_FRAME_TRANSMIT_REQUEST_64BIT_ADDRESS      = 0x00,
		XBEE_FRAME_TRANSMIT_REQUEST_16BIT_ADDRESS      = 0x01,
		XBEE_FRAME_AT_COMMAND                          = 0x08,
		XBEE_FRAME_AT_COMMAND_QUEUE_PARAMETER_VALUE    = 0x09,
		XBEE_FRAME_ZIGBEE_TRANSMIT_REQUEST             = 0x10,
		XBEE_FRAME_EXPL_ADDR_ZIGBEE_COMMAND_FRAME      = 0x11,
		XBEE_FRAME_REMOTE_AT_COMMAND_REQUEST           = 0x17,
		XBEE_FRAME_CREATE_SOURCE_ROUTE                 = 0x21,
		XBEE_FRAME_RECEIVE_PACKET_64BIT_ADDRESS        = 0x80,
		XBEE_FRAME_RECEIVE_PACKET_16BIT_ADDRESS        = 0x81,
		XBEE_FRAME_RECEIVE_PACKET_64BIT_ADDRESS_IO     = 0x82,
		XBEE_FRAME_RECEIVE_PACKET_16BIT_ADDRESS_IO     = 0x83,
		XBEE_FRAME_AT_COMMAND_RESPONSE                 = 0x88,
		XBEE_FRAME_MODEM_STATUS                        = 0x8A,
		XBEE_FRAME_ZIGBEE_TRANSMIT_STATUS              = 0x8B,
		XBEE_FRAME_TRANSMIT_STATUS                     = 0x89,
		XBEE_FRAME_ZIGBEE_RECEIVE_PACKET               = 0x90,
		XBEE_FRAME_ZIGBEE_EXPLICIT_RX_INDICATOR        = 0x91,
		XBEE_FRAME_ZIGBEE_IO_DATA_SAMPLE_RX_INDICATOR  = 0x92,
		XBEE_FRAME_XBEE_SENSOR_READ_INDICATOR          = 0x94,
		XBEE_FRAME_NODE_IDENTIFICATION_INDICATOR       = 0x95,
		XBEE_FRAME_REMOTE_AT_COMMAND_RESPONSE          = 0x97,
		XBEE_FRAME_OTA_FIRMWARE_UPDATE_STATUS          = 0xA0,
		XBEE_FRAME_ROUTE_RECORD_INDICATOR              = 0xA1,
		XBEE_FRAME_MANY_TO_ONE_ROUTE_REQUEST_INDICATOR = 0xA3,
		XBEE_FRAME_INVALID                             = 0xFF        
	};
	
	enum ReadStatus
	{
		XBEE_FRAME_OK,
		XBEE_FRAME_NOT_ENOUGH_DATA,
		XBEE_FRAME_NOT_FOUND
	};

	XBeeFrame();
		/// Creates an empty XBeeFrame.

	XBeeFrame(FrameType frameType, const char* data, std::size_t length);
		/// Creates a XBeeFrame of the given type, with the
		/// given frame data.

	XBeeFrame(FrameType frameType, const std::string& data);
		/// Creates a XBeeFrame of the given type, with the
		/// given frame data.
		
	XBeeFrame(const XBeeFrame& other);
		/// Creates a XBeeFrame by copying another one.	
		
	~XBeeFrame();
		/// Destroys the XBeeFrame.

	XBeeFrame& operator = (const XBeeFrame& other);
		/// Assignment operator.
		
	void swap(XBeeFrame& other);
		/// Swaps the contents of the frame with another one.
		
	FrameType type() const;
		/// Returns the frame type.	
		
	const char* data() const;
		/// Returns a pointer to the frame data.

	std::size_t dataSize() const;
		/// Returns the frame data size.
		
	const char* frame() const;
		/// Returns a pointer to the raw API frame.
		
	std::size_t frameSize() const;
		/// Returns the raw frame size.

	static ReadStatus read(XBeeFrame& frame, const char* buffer, std::size_t size);
		/// Attempts to read a frame from the given buffer.
		///
		/// Returns:
		///   - XBEE_FRAME_OK if a valid frame was found.
		///   - XBEE_FRAME_NOT_ENOUGH_DATA if the buffer does not contain enough data
		///     to read the entire frame. Retry again with a buffer containing more data.
		///   - XBEE_FRAME_NOT_FOUND if no valid frame was found.

	void escape();
		/// Escapes the frame, as required for AP=2 API mode.
		///
		/// When sending or receiving a UART data frame, specific data values must be 
		/// escaped (flagged) so they do not interfere with the UART or UART data frame 
		/// operation. To escape an interfering data byte, insert 0x7D and follow it 
		/// with the byte to be escaped XOR’d with 0x20.
		///
		/// Data bytes that need to be escaped:
		///   - 0x7E – Frame Delimiter
		///   - 0x7D – Escape
		///   - 0x11 – XON
		///   - 0x13 – XOFF
	
	void unescape();
		/// Unescapes the frame, if AP=2 API mode is used.
		///
		/// See escape() for more information.

protected:
	void init(FrameType frameType, const char* data, std::size_t length);
	unsigned char checksum() const;

private:
	std::vector<char> _frame;
};


//
// inlines
//
inline XBeeFrame::FrameType XBeeFrame::type() const
{
	return static_cast<FrameType>(static_cast<unsigned char>(_frame[3]));
}


inline const char* XBeeFrame::data() const
{
	return &_frame[4];
}


inline std::size_t XBeeFrame::dataSize() const
{
	return _frame.size() - 5;
}


inline const char* XBeeFrame::frame() const
{
	return &_frame[0];
}


inline std::size_t XBeeFrame::frameSize() const
{
	return _frame.size();
}


inline unsigned char XBeeFrame::checksum() const
{
	return static_cast<unsigned char>(_frame[_frame.size() - 1]);
}


} } // namespace IoT::XBee


#endif // IoT_XBee_XBeeFrame_INCLUDED
