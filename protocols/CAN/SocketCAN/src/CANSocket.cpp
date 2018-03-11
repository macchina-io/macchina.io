//
// CANSocket.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "CANSocket.h"
#include "Poco/Net/DatagramSocketImpl.h"
#ifdef MACCHINA_HAVE_SOCKETCAN
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <errno.h>
#include <cstring>
#endif // MACCHINA_HAVE_SOCKETCAN



namespace IoT {
namespace CAN {
namespace SocketCAN {


CANSocket::CANSocket(const std::string& interfc):
	Poco::Net::DatagramSocket(new Poco::Net::DatagramSocketImpl(canSocket(interfc)))
{
}


CANSocket::~CANSocket()
{
}


int CANSocket::canSocket(const std::string& interfc)
{
#ifdef MACCHINA_HAVE_SOCKETCAN
	if (interfc.size() >= IFNAMSIZ) throw Poco::InvalidArgumentException("interface name too long", interfc);

	int canFD = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);

	struct ifreq ifr;
	if (interfc.empty())
	{
		ifr.ifr_ifindex = 0;
	}
	else
	{
		std::strcpy(ifr.ifr_name, interfc.c_str());
		if (::ioctl(canFD, SIOCGIFINDEX, &ifr) == -1)
			throw Poco::IOException("Cannot map CAN interface name to index", interfc, errno);
	}

	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if (::bind(canFD, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1)
		throw Poco::IOException("Cannot bind CAN socket to interface", interfc, errno);

	return canFD;
#else
	throw Poco::NotImplementedException("SocketCAN not available on this platform");
#endif
}


} } } // namespace IoT::CAN::SocketCAN
