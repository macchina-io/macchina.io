//
// WebTunnelService.h
//
// Library: IoT/WebTunnel
// Package: WebTunnelService
// Module:  WebTunnelService
//
// Definition of the WebTunnelService interface.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebTunnel_WebTunnelService_INCLUDED
#define IoT_WebTunnel_WebTunnelService_INCLUDED


#include "IoT/WebTunnel/WebTunnel.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace WebTunnel {


//@ serialize
struct Property
{
	std::string name;
	std::string value;
};


//@ remote
class IoTWebTunnel_API WebTunnelService
	/// The interface for WebTunnel clients.
{
public:
	using Ptr = Poco::SharedPtr<WebTunnelService>;

	Poco::BasicEvent<void> connected;
		/// Fired when the WebTunnel connection with the server
		/// has been established.

	Poco::BasicEvent<void> disconnected;
		/// Fired when the WebTunnel connection with the server
		/// has been closed.

	WebTunnelService();
		/// Creates the WebTunnelService.

	virtual ~WebTunnelService();
		/// Destroys the WebTunnelService.

	virtual bool isConnected() const = 0;
		/// Returns true if a connection to the server is active,
		/// otherwise false.

	virtual void updateProperties(const std::vector<Property>& properties) = 0;
		/// Sends a device properties update to the server over the
		/// WebTunnel connection.

	static const std::string SERVICE_NAME;
};


} } // namespace IoT::WebTunnel


#endif // IoT_WebTunnel_WebTunnelService_INCLUDED
