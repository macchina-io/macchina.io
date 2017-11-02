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


TCPPort::TCPPort(const Poco::Net::SocketAddress& serverAddress):
	_serverAddress(serverAddress),
	_socket(serverAddress),
	_sendBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_receiveBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE)
{
}


	
TCPPort::~TCPPort()
{
	try
	{
		_socket.close();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


Poco::UInt8 TCPPort::receiveFrame(const Poco::Timespan& timeout)
{
	int n = _socket.receiveBytes(_receiveBuffer.begin(), MBAP_HEADER_SIZE);

	// A return value of 0 means a graceful shutdown of the connection from the peer.
	if(n == 0) 
	{
		throw Poco::Exception("Peer has shutdown the connection.");	
	}

	poco_assert(n == MBAP_HEADER_SIZE);

	Poco::MemoryInputStream istr(_receiveBuffer.begin(), _receiveBuffer.size());
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

	Poco::UInt16 transactionID;
	Poco::UInt16 protocolID;
	Poco::UInt16 length;
	binaryReader >> transactionID >> protocolID >> length;

	n = _socket.receiveBytes(_receiveBuffer.begin() + MBAP_HEADER_SIZE, length);

	// A return value of 0 means a graceful shutdown of the connection from the peer.
	if(n == 0) 
	{
		throw Poco::Exception("Peer has shutdown the connection.");	
	}

	poco_assert(n == length);
	
	return (n > 0) ? _receiveBuffer[MBAP_HEADER_SIZE + 1] : 0;
}


} } } // namespace IoT::Modbus::TCP
