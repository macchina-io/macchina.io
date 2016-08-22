//
// NetworkEnvironmentService.h
//
// $Id$
//
// Library: IoT/NetworkEnvironment
// Package: NetworkEnvironment
// Module:  NetworkEnvironmentService
//
// Definition of the NetworkEnvironmentService interface.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentService_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentService_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironment.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace NetworkEnvironment {


enum MIBInterfaceType
	/// MIB Interface Type
{
	MIB_TYPE_ETHERNET_CSMACD,
	MIB_TYPE_ISO88025_TOKENRING,
	MIB_TYPE_FRAMERELAY,
	MIB_TYPE_PPP,
	MIB_TYPE_SOFTWARE_LOOPBACK,
	MIB_TYPE_ATM,
	MIB_TYPE_IEEE80211,
	MIB_TYPE_TUNNEL,
	MIB_TYPE_IEEE1394,
	MIB_TYPE_OTHER
};


//@ serialize
struct AddressTuple
	/// IPv4/IPv6 address tuple.
{
	int version;
		/// IP address version - 4 or 6.
		
	std::string address;
		/// Bound IPv4 or IPv6 address.

	std::string subnetMask;
		/// Subnet Mask for IPv4.

	std::string broadcastOrDestinationAddress;
		/// IPv4 Broadcast address or destination address for 
		/// point-to-point interface.
};


//@ serialize
struct NetworkInterface
{
	unsigned index;
		/// The interface OS index.
		
	std::string name;
		/// The interface name.
		
	std::string displayName;
		/// The interface display name.
		///
		/// On Windows platforms, this is currently the network adapter
		/// name. This may change to the "friendly name" of the network
		/// connection in a future version, however. 
		///
		/// On other platforms this is the same as name.

	std::string adapterName;
		/// The interface adapter name.
		///
		/// On Windows platforms, this is the network adapter LUID.
		/// The adapter name is used by some Windows Net APIs like DHCP. 
		///
		/// On other platforms this is the same as name().

	std::string macAddress;
		/// The MAC (Media Access Control) address for the interface.
		
	std::vector<AddressTuple> addresses;
		/// The IP addresses assigned to this interface.

	unsigned mtu;
		/// The MTU for this interface.
		
	MIBInterfaceType type;
		/// The MIB IfType of the interface.
	
	bool supportsIP;
		/// True if the interface supports IP (4 or 6), otherwise false.

	bool supportsIPv4;
		/// True if the interface supports IPv4, otherwise false.
		
	bool supportsIPv6;
		/// True if the interface supports IPv6, otherwise false.

	bool supportsBroadcast;
		/// True if the interface supports broadcast, otherwise false.

	bool supportsMulticast;
		/// True if the interface supports multicast, otherwise false.

	bool isLoopback;
		/// True if the interface is a loopback interface, otherwise false.

	bool isPointToPoint;
		/// True if the interface is a point-to-point interface, otherwise false.

	bool isRunning;
		/// True if the interface is running, otherwise false.

	bool isUp;	
		/// True if the interface is up, otherwise false.
};


enum IPVersion
{
	IPv4_ONLY,    /// Return interfaces with IPv4 address only
	IPv6_ONLY,    /// Return interfaces with IPv6 address only
	IPv4_OR_IPv6  /// Return interfaces with IPv4 or IPv6 address
};


enum ChangeType
{
	NETENV_ADDRESS_ADDED = 1,
		/// An IP address has been added to the system.

	NETENV_ADDRESS_REMOVED = 2,
		/// An IP address has been removed from the system.
		
	NETENV_UNSPECIFIED = 3
		/// No detailed information about the environment change
		/// is available. This may also mean that an IP address
		/// has been added or removed.
};


enum EnumerateOptions
	/// Options for enumerateInterfaces().
{
	OPTION_INCLUDE_NON_IP = 1,
	OPTION_INCLUDE_DOWN   = 2
};


//@ remote
class IoTNetworkEnvironment_API NetworkEnvironmentService
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	typedef Poco::SharedPtr<NetworkEnvironmentService> Ptr;

	Poco::BasicEvent<const ChangeType> networkEnvironmentChanged;
		/// A change in the network environment has been detected.

	NetworkEnvironmentService();
		/// Creates the NetworkEnvironmentService.

	virtual ~NetworkEnvironmentService();
		/// Destroys the NetworkEnvironmentService.

	virtual std::string findActiveNetworkInterface(IPVersion ipVersion) = 0;
		/// Finds and returns the name of the first active network interface that 
		/// supports the given IP protocol version.
		///
		/// Throws a Poco::NotFoundException if no suitable network interface is found.
	
	//@ $options = {mandatory = false}
	virtual std::vector<NetworkInterface> enumerateInterfaces(int options = 0) = 0;
		/// Returns a vector containing available network interfaces.
		/// The options parameter can be used to include non-IP interfaces or
		/// interfaces that are down.
};


} } // namespace IoT::NetworkEnvironment


#endif // IoT_NetworkEnvironment_NetworkEnvironmentService_INCLUDED
