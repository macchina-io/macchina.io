//
// WebTunnelServiceEventDispatcher.h
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  WebTunnelServiceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebTunnel_WebTunnelServiceEventDispatcher_INCLUDED
#define IoT_WebTunnel_WebTunnelServiceEventDispatcher_INCLUDED


#include "IoT/WebTunnel/WebTunnelServiceRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace WebTunnel {


class WebTunnelServiceEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for WebTunnel clients.
{
public:
	WebTunnelServiceEventDispatcher(WebTunnelServiceRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a WebTunnelServiceEventDispatcher.

	virtual ~WebTunnelServiceEventDispatcher();
		/// Destroys the WebTunnelServiceEventDispatcher.

	void event__connected(const void* pSender);

	void event__disconnected(const void* pSender);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__connectedImpl(const std::string& subscriberURI);

	void event__disconnectedImpl(const std::string& subscriberURI);

	static const std::string DEFAULT_NS;
	WebTunnelServiceRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WebTunnelServiceEventDispatcher::remoting__typeId() const
{
	return IWebTunnelService::remoting__typeId();
}


} // namespace WebTunnel
} // namespace IoT


#endif // IoT_WebTunnel_WebTunnelServiceEventDispatcher_INCLUDED

