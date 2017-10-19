//
// TCPPort.cpp
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  TCPPort
//
// Copyright (c) 2015-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "TCPPort.h"


namespace IoT {
namespace Modbus {
namespace TCP {


TCPPort::TCPPort(const Poco::Net::SocketAddress& serverAddress, Poco::Timespan frameTimeout):
	_pSerialPort(pSerialPort),
	_frameTimeout(frameTimeout),
	_byteOrder(byteOrder),
	_sendBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_receiveBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE)
{
}

	
TCPPort::~TCPPort()
{
}


Poco::UInt8 TCPPort::receiveFrame(const Poco::Timespan& timeout)
{
	int n = _socket.receiveBytes(_receiveBuffer.begin(), MBAP_HEADER_SIZE);
	
	std::size_t n = 0;
	bool frameComplete = false;
	do
	{
		std::size_t rd = _pSerialPort->read(_receiveBuffer.begin() + n, _receiveBuffer.size() - n, _frameTimeout);
		if (rd == 0) return 0;
		if (rd == 1 && n == 0 && _receiveBuffer[0] == 0)
		{
			// ignore spurious null bytes before frame
			if (poll(timeout))
				continue;
			else
				throw Poco::TimeoutException();
		}
		n += rd;
		frameComplete = checkFrame(n);
	}
	while (!frameComplete && n < _receiveBuffer.size());
	
	return frameComplete ? _receiveBuffer[1] : 0;
}


} } } // namespace IoT::Modbus::TCP
