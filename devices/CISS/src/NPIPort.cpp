//
// NPIPort.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "NPIPort.h"
#include "NPIFrame.h"


namespace IoT {
namespace CISS {


NPIPort::NPIPort(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort):
	_pSerialPort(pSerialPort),
	_buffer(NPIFrame::CISS_MAX_FRAME_LENGTH)
{
}


NPIPort::~NPIPort()
{
}


void NPIPort::sendFrame(const NPIFrame& frame)
{
	_pSerialPort->write(frame.frame(), frame.frameSize());
}


std::size_t NPIPort::receiveFrame(NPIFrame& frame, const Poco::Timespan& timeout)
{
	std::size_t n = 0;
	NPIFrame::ReadStatus rs = NPIFrame::CISS_FRAME_NOT_FOUND;
	do
	{
		std::size_t rd = _pSerialPort->read(_buffer.begin() + n, 1, timeout);
		if (rd == 0) return 0;
		n += rd;
		rs = NPIFrame::read(frame, _buffer.begin(), n);
	}
	while (rs == NPIFrame::CISS_FRAME_NOT_ENOUGH_DATA && n < _buffer.size());

	return rs == NPIFrame::CISS_FRAME_OK ? n : 0;
}


} } // namespace IoT::CISS
