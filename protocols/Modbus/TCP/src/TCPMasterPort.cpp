//
// TCPMasterPort.cpp
//
// Library: IoT/Modbus/TCP
// Package: TCP
// Module:  TCPMasterPort
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/TCP/TCPMasterPort.h"
#include "Poco/Net/NetException.h"


using namespace std::string_literals;


namespace IoT {
namespace Modbus {
namespace TCP {


TCPMasterPort::TCPMasterPort(const Poco::Net::SocketAddress& serverAddress, Poco::Timespan connectTimeout, bool connectImmediately, std::size_t maxSimultaneousTransactions):
	_serverAddress(serverAddress),
	_connectTimeout(connectTimeout),
	_maxSimultaneousTransactions(maxSimultaneousTransactions),
	_socket(),
	_sendBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_receiveBuffer(MBAP_HEADER_SIZE + MAX_PDU_SIZE),
	_state(CONNECTION_CLOSED),
	_logger(Poco::Logger::get("IoT.Modbus.TCPMasterPort"s))
{
	try
	{
		if (connectImmediately) 
		{
			connect();
		}
	}
	catch (...)
	{
		poco_unexpected();
	}
}


TCPMasterPort::~TCPMasterPort()
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


Poco::UInt8 TCPMasterPort::receiveFrame()
{
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
		_logger.error(Poco::format("Error receiving frame from %s"s, exc.displayText()));
		disconnect();
		throw;
	}
	catch (Poco::Net::NetException& exc)
	{
		_logger.error(Poco::format("Error receiving frame from %s"s, exc.displayText()));
		disconnect();
		throw;
	}
}


void TCPMasterPort::reset()
{
	try
	{
		if (_state == CONNECTION_OPEN)
		{
			changeConnectionState(CONNECTION_CLOSING);
		}
		if (_socket.impl()->initialized())
		{
			_socket.close(); 
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.notice("Failed to disconnect: %s"s, exc.displayText());
	}
	changeConnectionState(CONNECTION_CLOSED);
}


void TCPMasterPort::disconnect(const bool active)
{
	if (_state != CONNECTION_OPEN) return;

	_logger.information("Disconnecting from %s"s, _serverAddress.toString());
	connectionStateChanged(this, CONNECTION_CLOSING);
	try
	{
		try
		{
			if (active)
			{
				_logger.debug("Shutting down connection to %s"s, _serverAddress.toString());
				_socket.shutdownSend();
				_logger.debug("Shut down connection to %s"s, _serverAddress.toString());
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Failed to shut down connection to %s: %s"s, _serverAddress.toString(), exc.displayText());
		}
		_logger.debug("Closing connection to %s"s, _serverAddress.toString());
		_socket.close();
		_logger.debug("Closed connection to %s"s, _serverAddress.toString());
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Failed to close connection to %s: %s"s, _serverAddress.toString(), exc.displayText());
	}

	// TODO: Improve failing closing state, at the moment set state in any case closed and notify connectionClosed event
	changeConnectionState(CONNECTION_CLOSED);
}


void TCPMasterPort::connect()
{
	if (_state == CONNECTION_OPEN) throw Poco::IllegalStateException("TCPMasterPort is alread in connected state");

	_logger.information("Connecting to %s..."s, _serverAddress.toString());
	try
	{
		changeConnectionState(CONNECTION_OPENING);
		_socket = Poco::Net::StreamSocket();
		_socket.connect(_serverAddress, _connectTimeout);
		_socket.setNoDelay(true);
		_logger.information("Connected to %s."s, _serverAddress.toString());
		changeConnectionState(CONNECTION_OPEN);
	}
	catch (Poco::TimeoutException& exc)
	{
		_logger.error("Failed to connect to %s: %s"s, _serverAddress.toString(), exc.displayText());
		_socket.close();
		changeConnectionState(CONNECTION_TIMEOUT);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Failed to connect to %s: %s"s, _serverAddress.toString(), exc.displayText());
		_socket.close();
		changeConnectionState(CONNECTION_ERROR);
	}
}

void TCPMasterPort::reconnectIfRequired()
{
	if (_state != CONNECTION_OPEN)
	{
		connect();
	}
	if (_state != CONNECTION_OPEN) throw Poco::IOException("Failed to reconnect to", _serverAddress.toString());
}


int TCPMasterPort::receiveBytes(void* buffer, int length)
{
	int n = _socket.receiveBytes(buffer, length);

	// A return value of 0 means a graceful shutdown of the connection from the peer.
	if (n == 0)
	{
		_logger.notice("Peer has shutdown the connection."s);
		disconnect(false);
		throw Poco::ProtocolException("Peer has shutdown the connection.");
	}

	poco_assert (n == length);

	return n;
}


} } } // namespace IoT::Modbus::TCP
