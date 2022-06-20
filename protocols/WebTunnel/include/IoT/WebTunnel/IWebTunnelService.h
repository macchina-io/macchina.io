//
// IWebTunnelService.h
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  IWebTunnelService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebTunnel_IWebTunnelService_INCLUDED
#define IoT_WebTunnel_IWebTunnelService_INCLUDED


#include "IoT/WebTunnel/WebTunnelService.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace WebTunnel {


class IWebTunnelService: public Poco::OSP::Service
	/// The interface for WebTunnel clients.
{
public:
	using Ptr = Poco::AutoPtr<IWebTunnelService>;

	IWebTunnelService();
		/// Creates a IWebTunnelService.

	virtual ~IWebTunnelService();
		/// Destroys the IWebTunnelService.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual bool isConnected() const = 0;
		/// Returns true if a connection to the server is active,
		/// otherwise false.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void updateProperties(const std::vector < IoT::WebTunnel::Property >& properties) = 0;
		/// Sends a device properties update to the server over the
		/// WebTunnel connection.

	Poco::BasicEvent < void > connected;
	Poco::BasicEvent < void > disconnected;
};


} // namespace WebTunnel
} // namespace IoT


#endif // IoT_WebTunnel_IWebTunnelService_INCLUDED

