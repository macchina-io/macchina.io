//
// WebTunnelServiceSkeleton.h
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  WebTunnelServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebTunnel_WebTunnelServiceSkeleton_INCLUDED
#define IoT_WebTunnel_WebTunnelServiceSkeleton_INCLUDED


#include "IoT/WebTunnel/WebTunnelServiceRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace WebTunnel {


class WebTunnelServiceSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for WebTunnel clients.
{
public:
	WebTunnelServiceSkeleton();
		/// Creates a WebTunnelServiceSkeleton.

	virtual ~WebTunnelServiceSkeleton();
		/// Destroys a WebTunnelServiceSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WebTunnelServiceSkeleton::remoting__typeId() const
{
	return IWebTunnelService::remoting__typeId();
}


} // namespace WebTunnel
} // namespace IoT


#endif // IoT_WebTunnel_WebTunnelServiceSkeleton_INCLUDED

