//
// TunnelSocketImpl.cpp
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  TunnelSocketImpl
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/TunnelSocketImpl.h"
#include "Poco/WebTunnel/Protocol.h"
#include "Poco/Net/NetException.h"
#include "Poco/Buffer.h"
#include <cstring>


namespace Poco {
namespace WebTunnel {


TunnelSocketImpl::TunnelSocketImpl(PortReflector& portReflector, PortReflector::TargetInfo::Ptr pTargetInfo, PortReflector::ChannelInfo::Ptr pChannelInfo):
	StreamSocketImpl(pTargetInfo->pWebSocket->impl()->sockfd()),
	_portReflector(portReflector),
	_pTargetInfo(pTargetInfo),
	_pChannelInfo(pChannelInfo),
	_writeBuffer(Protocol::WT_FRAME_MAX_SIZE + Protocol::WT_FRAME_HEADER_SIZE),
	_readBuffer(8192),
	_statusCode(Protocol::WT_ERR_NONE),
	_sendTimeout(60, 0),
	_receiveTimeout(30, 0),
	_logger(Poco::Logger::get("WebTunnel.TunnelSocketImpl"))
{
}


TunnelSocketImpl::~TunnelSocketImpl()
{
}


int TunnelSocketImpl::sendBytes(const void* buffer, int length, int flags)
{
	while (_pChannelInfo->state == PortReflector::CS_CONNECTING)
	{
		_logger.debug("Sending data: waiting for channel to be connected...");
		if (!_pChannelInfo->stateChanged.tryWait(CONNECT_TIMEOUT))
		{
			_pChannelInfo->state = PortReflector::CS_ERROR;
			_portReflector.removeTarget(_pTargetInfo);
			throw Poco::TimeoutException();
		}
	}

	if (_pChannelInfo->state != PortReflector::CS_CONNECTED)
	{
		if (_pChannelInfo->state == PortReflector::CS_DISCONNECTED)
		{
			switch (_statusCode)
			{
			case Protocol::WT_ERR_CONN_REFUSED:
				throw Poco::Net::ConnectionRefusedException();
			case Protocol::WT_ERR_TIMEOUT:
				throw Poco::TimeoutException();
			case Protocol::WT_ERR_SOCKET:
				throw Poco::Net::NetException();
			}
		}
		else if (_logger.debug())
		{
			_logger.debug(Poco::format("Illegal channel state for channel %hu: %d", _pChannelInfo->channel, static_cast<int>(_pChannelInfo->state)));
		}
		return 0;
	}

	int sent = 0;
	try
	{
		const char* pB = reinterpret_cast<const char*>(buffer);
		while (length > 0)
		{
			std::size_t hn = Protocol::writeHeader(_writeBuffer.begin(), _writeBuffer.size(), Protocol::WT_OP_DATA, 0, _pChannelInfo->channel);
			int frameLength = length;
			if (frameLength > Protocol::WT_FRAME_MAX_SIZE) frameLength = Protocol::WT_FRAME_MAX_SIZE;
			std::memcpy(_writeBuffer.begin() + hn, pB, frameLength);
			Poco::FastMutex::ScopedLock lock(_pTargetInfo->webSocketMutex);
			_pTargetInfo->pWebSocket->sendFrame(_writeBuffer.begin(), static_cast<int>(frameLength + hn), Poco::Net::WebSocket::FRAME_BINARY);
			length -= frameLength;
			sent += frameLength;
			pB += frameLength;
		}
	}
	catch (Poco::Exception&)
	{
		_portReflector.removeTarget(_pTargetInfo);
		return 0;
	}
	return sent;
}


int TunnelSocketImpl::receiveBytes(void* buffer, int length, int)
{
	int n = _readBuffer.read(reinterpret_cast<char*>(buffer), length, static_cast<long>(_receiveTimeout.totalMilliseconds()));
	if (n == 0)
	{
		switch (_statusCode)
		{
		case Protocol::WT_ERR_CONN_REFUSED:
			throw Poco::Net::ConnectionRefusedException();
		case Protocol::WT_ERR_TIMEOUT:
			throw Poco::TimeoutException();
		case Protocol::WT_ERR_SOCKET:
			throw Poco::Net::NetException();
		}
	}
	return n;
}


int TunnelSocketImpl::enqueueBytes(const char* buffer, int size)
{
	return _readBuffer.write(buffer, size, BUFFER_TIMEOUT);
}


void TunnelSocketImpl::enqueueClose(Poco::UInt16 statusCode)
{
	_statusCode = statusCode;
	return _readBuffer.close();
}


Poco::Net::SocketImpl* TunnelSocketImpl::acceptConnection(Poco::Net::SocketAddress& clientAddr)
{
	throw Poco::InvalidAccessException("Cannot acceptConnection() on a TunnelSocketImpl");
}


void TunnelSocketImpl::connect(const Poco::Net::SocketAddress& address)
{
	throw Poco::InvalidAccessException("Cannot connect() a TunnelSocketImpl");
}


void TunnelSocketImpl::connect(const Poco::Net::SocketAddress& address, const Poco::Timespan& timeout)
{
	throw Poco::InvalidAccessException("Cannot connect() a TunnelSocketImpl");
}


void TunnelSocketImpl::connectNB(const Poco::Net::SocketAddress& address)
{
	throw Poco::InvalidAccessException("Cannot connectNB() a TunnelSocketImpl");
}


void TunnelSocketImpl::bind(const Poco::Net::SocketAddress& address, bool reuseAddress)
{
	throw Poco::InvalidAccessException("Cannot bind() a TunnelSocketImpl");
}


void TunnelSocketImpl::bind6(const Poco::Net::SocketAddress& address, bool reuseAddress, bool ipV6Only)
{
	throw Poco::InvalidAccessException("Cannot bind6() a TunnelSocketImpl");
}


void TunnelSocketImpl::listen(int backlog)
{
	throw Poco::InvalidAccessException("Cannot listen() on a TunnelSocketImpl");
}


void TunnelSocketImpl::close()
{
	if (!initialized()) return;

	try
	{
		while (_pChannelInfo->state == PortReflector::CS_CONNECTING)
		{
			_logger.debug("Closing: waiting for channel to be connected...");
			_pChannelInfo->stateChanged.wait(CONNECT_TIMEOUT);
		}

		if (_pChannelInfo->state == PortReflector::CS_CONNECTED)
		{
			_portReflector.shutdownChannel(_pTargetInfo, _pChannelInfo);
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.warning(Poco::format("Error closing TunnelSocket: %s", exc.displayText()));
	}

	reset();
	_pChannelInfo = 0;
	_pTargetInfo = 0;
}


void TunnelSocketImpl::shutdownReceive()
{
	throw Poco::InvalidAccessException("Cannot shutdownReceive() on a TunnelSocketImpl");
}


void TunnelSocketImpl::shutdownSend()
{
	throw Poco::InvalidAccessException("Cannot shutdownSend() on a TunnelSocketImpl");
}


void TunnelSocketImpl::shutdown()
{
	throw Poco::InvalidAccessException("Cannot shutdown() on a TunnelSocketImpl");
}


int TunnelSocketImpl::sendTo(const void* buffer, int length, const Poco::Net::SocketAddress& address, int flags)
{
	throw Poco::InvalidAccessException("Cannot sendTo() on a TunnelSocketImpl");
}


int TunnelSocketImpl::receiveFrom(void* buffer, int length, Poco::Net::SocketAddress& address, int flags)
{
	throw Poco::InvalidAccessException("Cannot receiveFrom() on a TunnelSocketImpl");
}


void TunnelSocketImpl::sendUrgent(unsigned char data)
{
	throw Poco::InvalidAccessException("Cannot sendUrgent() on a TunnelSocketImpl");
}


bool TunnelSocketImpl::secure() const
{
	return false;
}


void TunnelSocketImpl::setSendTimeout(const Poco::Timespan& timeout)
{
	_sendTimeout = timeout;
}


Poco::Timespan TunnelSocketImpl::getSendTimeout()
{
	return _sendTimeout;
}


void TunnelSocketImpl::setReceiveTimeout(const Poco::Timespan& timeout)
{
	_receiveTimeout = timeout;
}


Poco::Timespan TunnelSocketImpl::getReceiveTimeout()
{
	return _receiveTimeout;
}


} } // namespace Poco::WebTunnel
