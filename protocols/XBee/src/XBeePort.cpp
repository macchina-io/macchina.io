//
// XBeePort.cpp
//
// Library: IoT/XBee
// Package: XBee
// Module:  XBeePort
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/XBeePort.h"
#include "IoT/XBee/XBeeFrame.h"


namespace IoT {
namespace XBee {


XBeePort::XBeePort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort):
	_pSerialPort(pSerialPort),
	_buffer(XBeeFrame::XBEE_MAX_FRAME_LENGTH)
{
}

	
XBeePort::~XBeePort()
{
}


void XBeePort::sendFrame(const XBeeFrame& frame)
{
	_pSerialPort->write(frame.frame(), frame.frameSize());
}


std::size_t XBeePort::receiveFrame(XBeeFrame& frame)
{
	std::size_t n = 0;
	XBeeFrame::ReadStatus rs = XBeeFrame::XBEE_FRAME_NOT_FOUND;
	do
	{
		n += _pSerialPort->read(_buffer.begin() + n, _buffer.size() - n);
		rs = XBeeFrame::read(frame, _buffer.begin(), n);
	}
	while (rs == XBeeFrame::XBEE_FRAME_NOT_ENOUGH_DATA && n < _buffer.size());
	
	return rs == XBeeFrame::XBEE_FRAME_OK ? n : 0;
}

	
std::size_t XBeePort::receiveFrame(XBeeFrame& frame, const Poco::Timespan& timeout)
{
	std::size_t n = 0;
	XBeeFrame::ReadStatus rs = XBeeFrame::XBEE_FRAME_NOT_FOUND;
	do
	{
		std::size_t rd = _pSerialPort->read(_buffer.begin() + n, _buffer.size() - n, timeout);
		if (rd == 0) return 0;
		n += rd;
		rs = XBeeFrame::read(frame, _buffer.begin(), n);
	}
	while (rs == XBeeFrame::XBEE_FRAME_NOT_ENOUGH_DATA && n < _buffer.size());
	
	return rs == XBeeFrame::XBEE_FRAME_OK ? n : 0;
}


} } // namespace IoT::XBee
