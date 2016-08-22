//
// NetworkEnvironmentServiceImpl.h
//
// $Id$
//
// Library: IoT/NetworkEnvironment
// Package: NetworkEnvironment
// Module:  NetworkEnvironmentServiceImpl
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceImpl.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Thread.h"
#include "Poco/Event.h"
#include "Poco/Runnable.h"
#include "Poco/Logger.h"
#include <algorithm>
#include <sstream>
#include <set>


#if POCO_OS == POCO_OS_LINUX
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/StreamSocketImpl.h"
#include "Poco/Buffer.h"
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#endif


namespace IoT {
namespace NetworkEnvironment {


class NetworkMonitorThread: public Poco::Runnable
{
public:	
	NetworkMonitorThread(NetworkEnvironmentServiceImpl& netEnvService, Poco::Logger& logger):
		_netEnvService(netEnvService),
		_logger(logger)
	{
	}
	
	~NetworkMonitorThread()
	{
	}
	
	void start()
	{
		_thread.start(*this);
	}
	
	void stop()
	{
		_stopped.set();
		_thread.join();
	}
	
	void notify(ChangeType lastChange)
	{
		try
		{
			_logger.information("Network environment change detected.");
			_netEnvService.networkEnvironmentChanged(this, lastChange);
		}
		catch (Poco::Exception& exc)
		{
			_logger.warning("Unhandled exception in delegate: " + exc.displayText());
		}
		catch (...)
		{
			_logger.warning("Unhandled exception in delegate.");
		}
	}
		
	void run()
	{
#if POCO_OS == POCO_OS_LINUX
		int sockfd;
		if ((sockfd = ::socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE)) == -1) 
		{
			throw Poco::IOException("cannot create netlink socket");
		}

		struct sockaddr_nl addr;
		memset(&addr, 0, sizeof(addr));
		addr.nl_family = AF_NETLINK;
		addr.nl_groups = RTMGRP_IPV4_IFADDR;

		if (::bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) == -1) 
		{
			::close(sockfd);
			throw Poco::IOException("cannot bind netlink socket");
		}
	
		Poco::Net::StreamSocket socket(new Poco::Net::StreamSocketImpl(sockfd));
		Poco::Buffer<char> buffer(4096);
		bool pendingChange = false;
		NetEnvService::NetEnvChange lastChange = NETENV_UNSPECIFIED;
		while (!_stopped.tryWait(0))
		{
			try
			{
				if (socket.poll(Poco::Timespan(0, 250000), Poco::Net::Socket::SELECT_READ))
				{
					int n = socket.receiveBytes(buffer.begin(), buffer.size());
					if (n > 0)
					{
						struct nlmsghdr* nlh = reinterpret_cast<struct nlmsghdr*>(buffer.begin());
						while ((NLMSG_OK(nlh, n)) && (nlh->nlmsg_type != NLMSG_DONE)) 
						{
							if (nlh->nlmsg_type == RTM_NEWADDR) 
							{
								if (pendingChange && lastChange != NETENV_ADDRESS_ADDED)
									lastChange = NETENV_UNSPECIFIED;
								else
									lastChange = NETENV_ADDRESS_ADDED;
								pendingChange = true;
							}
							else if (nlh->nlmsg_type == RTM_DELADDR)
							{
								if (pendingChange && lastChange != NETENV_ADDRESS_REMOVED)
									lastChange = NETENV_UNSPECIFIED;
								else
									lastChange = NETENV_ADDRESS_REMOVED;
								pendingChange = true;
							}
							nlh = NLMSG_NEXT(nlh, n);
						}
					}
				}
				else if (pendingChange)
				{
					pendingChange = false;
					notify(lastChange);
					lastChange = NETENV_UNSPECIFIED;
				}
			}
			catch (Poco::Exception& exc)
			{
				_logger.log(exc);
			}
		}
#else
		std::set<Poco::Net::IPAddress> addrSet;
		std::vector<Poco::Net::NetworkInterface> ifList = Poco::Net::NetworkInterface::list();
		for (std::vector<Poco::Net::NetworkInterface>::const_iterator it = ifList.begin(); it != ifList.end(); ++it)
		{
			addrSet.insert(it->address());
		}
		while (!_stopped.tryWait(10000))
		{
			try
			{
				std::set<Poco::Net::IPAddress> newAddrSet;
				ifList = Poco::Net::NetworkInterface::list();
				for (std::vector<Poco::Net::NetworkInterface>::const_iterator it = ifList.begin(); it != ifList.end(); ++it)
				{
					newAddrSet.insert(it->address());
				}
				if (newAddrSet != addrSet)
				{
					std::swap(addrSet, newAddrSet);
					notify(NETENV_UNSPECIFIED);
				}
			}
			catch (Poco::Exception& exc)
			{
				_logger.log(exc);
			}
		}
#endif
	}
	
private:
	Poco::Thread _thread;
	NetworkEnvironmentServiceImpl& _netEnvService;
	Poco::Event _stopped;
	Poco::Logger& _logger;
};


NetworkEnvironmentServiceImpl::NetworkEnvironmentServiceImpl():
	_pMonitorThread(new NetworkMonitorThread(*this, Poco::Logger::get("IoT.NetworkEnvironment")))
{
	_pMonitorThread->start();
}


NetworkEnvironmentServiceImpl::~NetworkEnvironmentServiceImpl()
{
	try
	{
		_pMonitorThread->stop();
	}
	catch (...)
	{
		poco_unexpected();
	}

	delete _pMonitorThread;
}


std::string NetworkEnvironmentServiceImpl::findActiveNetworkInterface(IPVersion ipVersion)
{
	Poco::Net::NetworkInterface::NetworkInterfaceList ifs = Poco::Net::NetworkInterface::list();
	for (Poco::Net::NetworkInterface::NetworkInterfaceList::iterator it = ifs.begin(); it != ifs.end(); ++it)
	{
		if (!it->address().isWildcard() && !it->address().isLoopback()) 
		{
			switch (ipVersion)
			{
			case IPv4_ONLY:
				if (it->address().family() == Poco::Net::IPAddress::IPv4)
					return it->name();
				break;
			case IPv6_ONLY:
				if (it->address().family() == Poco::Net::IPAddress::IPv6)
					return it->name();
				break;
			default:
				return it->name();
			}
		}
	}
	throw Poco::NotFoundException("No configured network interface found");
}


std::vector<NetworkInterface> NetworkEnvironmentServiceImpl::enumerateInterfaces(int options)
{
	std::vector<NetworkInterface> result;
	
	bool ipOnly = (options & OPTION_INCLUDE_NON_IP) == 0;
	bool upOnly = (options & OPTION_INCLUDE_DOWN) == 0;
	Poco::Net::NetworkInterface::Map map = Poco::Net::NetworkInterface::map(ipOnly, upOnly);
	
	for (Poco::Net::NetworkInterface::Map::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		NetworkInterface intf;
		intf.index       = it->second.index();
		intf.name        = it->second.name();
		intf.displayName = it->second.displayName();
		intf.adapterName = it->second.adapterName();
		
		std::ostringstream macStream;
		macStream << it->second.macAddress();
		intf.macAddress  = macStream.str();
		
		intf.mtu                = it->second.mtu();
		intf.type               = static_cast<MIBInterfaceType>(it->second.type());
		intf.supportsIP         = it->second.supportsIP();
		intf.supportsIPv4       = it->second.supportsIPv4();
		intf.supportsIPv6       = it->second.supportsIPv6();
		intf.supportsBroadcast  = it->second.supportsBroadcast();
		intf.supportsMulticast  = it->second.supportsMulticast();
		intf.isLoopback         = it->second.isLoopback();
		intf.isPointToPoint     = it->second.isPointToPoint();
		intf.isRunning          = it->second.isRunning();
		intf.isUp               = it->second.isUp();
	
		const Poco::Net::NetworkInterface::AddressList& addrList = it->second.addressList();
		for (Poco::Net::NetworkInterface::AddressList::const_iterator ita = addrList.begin(); ita != addrList.end(); ++ita)
		{
			AddressTuple addr;
			addr.version = (ita->get<0>().family() == Poco::Net::IPAddress::IPv4) ? 4 : 6;
			addr.address = ita->get<0>().toString();
			if (addr.version == 4)
			{
				addr.subnetMask = ita->get<1>().toString();
			}
			if (it->second.supportsBroadcast() || it->second.isPointToPoint())
			{
				addr.broadcastOrDestinationAddress = ita->get<2>().toString();
			}
			intf.addresses.push_back(addr);
		}
		
		result.push_back(intf);
	}

	return result;
}


} } // namespace IoT::NetworkEnvironment
