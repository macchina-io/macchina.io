//
// UDPEndpointImpl.cpp
//
// Library: IoT/UDP
// Package: UDPEndpoint
// Module:  UDPEndpoint
///
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/UDP/UDPEndpointImpl.h"
#include "Poco/Buffer.h"


namespace IoT {
namespace UDP {


UDPEndpointImpl::UDPEndpointImpl(const Poco::Net::SocketAddress& addr):
	_socket(addr, true),
	_handlePackets(this, &UDPEndpointImpl::handlePackets),
	_logger(Poco::Logger::get("UDPEndpointImpl"))
{
	_handlePackets.start();
}


UDPEndpointImpl::~UDPEndpointImpl()
{
	_handlePackets.stop();
}


void UDPEndpointImpl::connect(const Poco::Net::SocketAddress& addr)
{
	_socket.connect(addr);
}


EndpointAddress UDPEndpointImpl::address() const
{
	Poco::Net::SocketAddress addr = _socket.address();

	EndpointAddress result;
	result.ipAddress = addr.host().toString();
	result.port = addr.port();
	return result;
}


void UDPEndpointImpl::sendPacket(const std::vector<char>& payload, const EndpointAddress& destination)
{
	if (destination.ipAddress.empty() || destination.port == 0)
	{
		_socket.sendBytes(&payload[0], static_cast<int>(payload.size()));
	}
	else
	{
		Poco::Net::SocketAddress addr(destination.ipAddress, destination.port);
		_socket.sendTo(&payload[0], static_cast<int>(payload.size()), addr);
	}
}


void UDPEndpointImpl::handlePackets()
{
	Poco::Buffer<char> buffer(MAX_MESSAGE_SIZE);
	while (!_handlePackets.isStopped())
	{
		try
		{
			if (_socket.poll(Poco::Timespan(POLL_TIMEOUT), Poco::Net::Socket::SELECT_READ))
			{
				Poco::Net::SocketAddress sa;
				int n = _socket.receiveFrom(buffer.begin(), buffer.size(), sa);
				Packet packet;
				packet.source.ipAddress = sa.host().toString();
				packet.source.port = sa.port();
				packet.destination.ipAddress = _socket.address().host().toString();
				packet.destination.port = _socket.address().port();
				packet.payload.assign(buffer.begin(), buffer.begin() + n);
				
				this->packetReceived(this, packet);
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
}


} } // namespace IoT::UDP
