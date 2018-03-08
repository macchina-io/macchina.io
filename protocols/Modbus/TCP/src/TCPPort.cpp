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
#include "Poco/Net/NetException.h"


namespace IoT {
namespace Modbus {
namespace TCP {


TCPPort::TCPPort(const Poco::Net::SocketAddress& serverAddress):
	_serverAddress(serverAddress),
	_socket(),
	_sendBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_receiveBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_state(STATE_CLOSED),
	_logger(Poco::Logger::get("IoT.Modbus.TCPPort"))
{
	try
	{
		connect();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


	
TCPPort::~TCPPort()
{
	try
	{
		disconnect();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


Poco::UInt8 TCPPort::receiveFrame(const Poco::Timespan& timeout)
{
	reconnectIfRequired();
	
	try 
	{

		receiveBytes(_receiveBuffer.begin(), MBAP_HEADER_SIZE);

		Poco::MemoryInputStream istr(_receiveBuffer.begin(), _receiveBuffer.size());
		Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);

		Poco::UInt16 transactionID;
		Poco::UInt16 protocolID;
		Poco::UInt16 length;
		binaryReader >> transactionID >> protocolID >> length;

		int n = receiveBytes(_receiveBuffer.begin() + MBAP_HEADER_SIZE, length);

		return (n > 0) ? _receiveBuffer[MBAP_HEADER_SIZE + 1] : 0;

	}
	catch (Poco::TimeoutException& exc)
	{
		_logger.error(Poco::format("Error receiving frame on TCP socket: %s", exc.displayText()));
		disconnect();
		throw exc;
	}
	catch (Poco::Net::NetException& exc)
	{
		_logger.error(Poco::format("Error receiving frame on TCP socket: %s", exc.displayText()));
		disconnect();
		throw exc;
	}	
}


void TCPPort::disconnect(const bool active)
{
	_logger.information("Disconnecting from tcp port '%s'", _serverAddress.toString());
	if(_state == STATE_CLOSED) throw Poco::IOException("TCPPort is already in closed state");
	connectionClosing(this);
	try
	{
		try
		{
			if (active)
			{
				_logger.information("Shutting down tcp socket '%s'", _serverAddress.toString());
				_socket.shutdown();
				_logger.information("Shutted down tcp socket '%s'", _serverAddress.toString());
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Failed to shut down tcp socket '%s': %s", _serverAddress.toString(), exc.displayText());
		}
		_logger.information("Closing tcp socket '%s'", _serverAddress.toString());
		_socket.close();		
		_logger.information("Closed tcp socket '%s'", _serverAddress.toString());
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Failed to close tcp socket '%s': %s", _serverAddress.toString(), exc.displayText());
	}

	// TODO Improve failing closing state, at the moment set state in any case closed and notify connectionClosed event :
	_state = STATE_CLOSED;
	connectionClosed(this);
}


void TCPPort::connect()
{
	_logger.information("Connecting to tcp port '%s'", _serverAddress.toString());
	if(_state == STATE_ESTABLISHED) throw Poco::IOException("TCPPort is alread in etablished state");
	try
	{
		_socket.connect(_serverAddress);
		_state = STATE_ESTABLISHED;
		_logger.information("Connected to tcp port '%s'", _serverAddress.toString());
		connectionEstablished(this);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Failed to connect to tcp port '%s': %s", _serverAddress.toString(), exc.displayText());
	}
}

void TCPPort::reconnectIfRequired()
{
	if(_state == STATE_CLOSED)
	{
		_logger.notice("Try reconnect to tcp port '%s'", _serverAddress.toString());
		connect();
	}
	if(_state != STATE_ESTABLISHED) throw Poco::IOException("TCPPort is not in established state");
}


int TCPPort::receiveBytes(void* buffer, int length)
{
	int n = _socket.receiveBytes(buffer, length);

	// A return value of 0 means a graceful shutdown of the connection from the peer.
	if(n == 0) 
	{
		_logger.notice("Peer has shutdown the connection.");
		disconnect(false);	
		throw Poco::ProtocolException("Peer has shutdown the connection.");
	}

	poco_assert(n == length);

	return n;
}


} } } // namespace IoT::Modbus::TCP
