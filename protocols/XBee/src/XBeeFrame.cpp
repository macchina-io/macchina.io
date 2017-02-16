//
// XBeeFrame.cpp
//
// $Id$
//
// Library: IoT/XBee
// Package: XBee
// Module:  XBeeFrame
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/XBeeFrame.h"
#include <algorithm>


namespace IoT {
namespace XBee {


XBeeFrame::XBeeFrame():
	_frame(5, 0)
{
	init(XBEE_FRAME_INVALID, 0, 0);
}


XBeeFrame::XBeeFrame(FrameType frameType, const char* data, std::size_t length):
	_frame(length + 5, 0)
{
	init(frameType, data, length);
}


XBeeFrame::XBeeFrame(FrameType frameType, const std::string& data):
	_frame(data.length() + 5, 0)
{
	init(frameType, data.data(), data.length());
}

	
XBeeFrame::XBeeFrame(const XBeeFrame& other):
	_frame(other._frame)
{
}

	
XBeeFrame::~XBeeFrame()
{
}


void XBeeFrame::init(FrameType frameType, const char* data, std::size_t length)
{
	poco_assert (length <= XBEE_MAX_DATA_LENGTH);
	
	_frame[0] = XBEE_FRAME_START_DELIM;
	std::size_t fullLength = length + 1;
	_frame[1] = static_cast<char>(fullLength >> 8);
	_frame[2] = static_cast<char>(fullLength & 0xFF);
	_frame[3] = static_cast<char>(frameType);
	Poco::UInt32 checksum = frameType;
	for (std::size_t i = 0; i < length; i++)
	{
		_frame[i + 4] = data[i];
		checksum += static_cast<unsigned char>(data[i]);
	}
	_frame[_frame.size() - 1] = static_cast<char>(0xFF - (checksum & 0xFF));
}


XBeeFrame& XBeeFrame::operator = (const XBeeFrame& other)
{
	_frame = other._frame;
	return *this;
}

	
void XBeeFrame::swap(XBeeFrame& other)
{
	std::swap(_frame, other._frame);
}


XBeeFrame::ReadStatus XBeeFrame::read(XBeeFrame& frame, const char* buffer, std::size_t size)
{
	std::size_t i = 0;
	while (i < size)
	{
		while (i < size && buffer[i] != XBEE_FRAME_START_DELIM) i++;
		if (i < size)
		{
			if (i + 2 + 1 < size) // 2 length bytes + checksum
			{
				std::size_t dataSize = static_cast<unsigned char>(buffer[i + 1])*256 + static_cast<unsigned char>(buffer[i + 2]);
				if (dataSize <= XBEE_MAX_DATA_LENGTH)
				{
					if (i + 2 + dataSize + 1 < size) // 2 length bytes + data + checksum
					{
						XBeeFrame tempFrame(static_cast<FrameType>(buffer[i + 3]), buffer + 4, dataSize - 1);
						if (tempFrame.checksum() == static_cast<unsigned char>(buffer[i + 2 + dataSize + 1]))
						{
							frame.swap(tempFrame);
							return XBEE_FRAME_OK;
						}
					}
					else return XBEE_FRAME_NOT_ENOUGH_DATA;
				}
				i++;
			}
			else return XBEE_FRAME_NOT_ENOUGH_DATA;
		}
	}
	return XBEE_FRAME_NOT_FOUND;
}


void XBeeFrame::escape()
{
	if (_frame.empty()) return;
	
	std::vector<char> escapedFrame;
	escapedFrame.reserve(_frame.size()*4/3);
	std::vector<char>::const_iterator it = _frame.begin();
	escapedFrame.push_back(*it++); // don't escape start delimiter
	for (; it != _frame.end(); ++it)
	{
		switch (*it)
		{
		case 0x7E:
		case 0x7D:
		case 0x11:
		case 0x13:
			escapedFrame.push_back(0x7D);
			escapedFrame.push_back(*it ^ 0x20);
			break;
		default:
			escapedFrame.push_back(*it);
			break;
		}
	}
	std::swap(_frame, escapedFrame);
}


void XBeeFrame::unescape()
{
	if (_frame.empty()) return;

	std::vector<char> unescapedFrame;
	unescapedFrame.reserve(_frame.size());
	std::vector<char>::const_iterator it = _frame.begin();
	unescapedFrame.push_back(*it++); // don't escape start delimiter
	while (it != _frame.end())
	{
		if (*it == 0x7D)
		{
			++it;
			if (it != _frame.end())
			{
				unescapedFrame.push_back(*it ^ 0x20);
			}
		}
		else
		{
			unescapedFrame.push_back(*it);
		}
		it++;
	}
	std::swap(_frame, unescapedFrame);
}


} } // namespace IoT::XBee
