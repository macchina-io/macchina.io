//
// WebTunnelServiceRemoteObject.h
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  WebTunnelServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebTunnel_WebTunnelServiceRemoteObject_INCLUDED
#define IoT_WebTunnel_WebTunnelServiceRemoteObject_INCLUDED


#include "IoT/WebTunnel/IWebTunnelService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace WebTunnel {


class WebTunnelServiceRemoteObject: public IoT::WebTunnel::IWebTunnelService, public Poco::RemotingNG::RemoteObject
	/// The interface for WebTunnel clients.
{
public:
	using Ptr = Poco::AutoPtr<WebTunnelServiceRemoteObject>;

	WebTunnelServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject);
		/// Creates a WebTunnelServiceRemoteObject.

	virtual ~WebTunnelServiceRemoteObject();
		/// Destroys the WebTunnelServiceRemoteObject.

	virtual bool isConnected() const;
		/// Returns true if a connection to the server is active,
		/// otherwise false.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void updateProperties(const std::vector<IoT::WebTunnel::Property>& properties);
		/// Sends a device properties update to the server over the
		/// WebTunnel connection.

protected:
	void event__connected();

	void event__disconnected();

private:
	Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> _pServiceObject;
};


inline bool WebTunnelServiceRemoteObject::isConnected() const
{
	return _pServiceObject->isConnected();
}


inline const Poco::RemotingNG::Identifiable::TypeId& WebTunnelServiceRemoteObject::remoting__typeId() const
{
	return IWebTunnelService::remoting__typeId();
}


inline void WebTunnelServiceRemoteObject::updateProperties(const std::vector<IoT::WebTunnel::Property>& properties)
{
	_pServiceObject->updateProperties(properties);
}


} // namespace WebTunnel
} // namespace IoT


#endif // IoT_WebTunnel_WebTunnelServiceRemoteObject_INCLUDED

