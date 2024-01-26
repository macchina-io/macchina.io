//
// TCPDevicePort.cpp
//
// Library: IoT/Modbus/TCP
// Package: TCP
// Module:  TCPDevicePort
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/TCP/TCPDevicePort.h"
#include "Poco/Net/NetException.h"


using namespace std::string_literals;


namespace IoT {
namespace Modbus {
namespace TCP {


TCPDevicePort::TCPDevicePort(const Poco::Net::StreamSocket& socket):
	_socket(socket),
	_sendBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_receiveBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_logger(Poco::Logger::get("IoT.Modbus.TCPDevicePort"s))
{
	try
	{
		_socket.setNoDelay(true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


TCPDevicePort::~TCPDevicePort()
{
}


Poco::UInt8 TCPDevicePort::receiveFrame()
{
	try
	{
		int n = receiveBytes(_receiveBuffer.begin(), MBAP_HEADER_SIZE);
		if (n == 0) return 0;

		Poco::MemoryInputStream istr(_receiveBuffer.begin(), _receiveBuffer.size());
		Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

		Poco::UInt16 transactionID;
		Poco::UInt16 protocolID;
		Poco::UInt16 length;
		binaryReader >> transactionID >> protocolID >> length;

		n = receiveBytes(_receiveBuffer.begin() + MBAP_HEADER_SIZE, length);

		return (n > 0) ? _receiveBuffer[MBAP_HEADER_SIZE + 1] : 0;

	}
	catch (Poco::TimeoutException& exc)
	{
		_logger.error(Poco::format("Error receiving frame: %s"s, exc.displayText()));
		disconnect();
		throw;
	}
	catch (Poco::Net::NetException& exc)
	{
		_logger.error(Poco::format("Error receiving frame: %s"s, exc.displayText()));
		disconnect();
		throw;
	}
}


void TCPDevicePort::disconnect()
{
	try
	{
		_socket.close();
	}
	catch (Poco::Exception& exc)
	{
	}
	_isConnected = false;
}


int TCPDevicePort::receiveBytes(char* buffer, int length)
{
	int received = 0;
	while (received < length)
	{
		int n = _socket.receiveBytes(buffer + received, length - received);
		if (n == 0)
		{
			_logger.notice("Peer has closed the connection."s);
			disconnect();
			return 0;
		}
		received += n;
	}
	return received;
}


} } } // namespace IoT::Modbus::TCP
