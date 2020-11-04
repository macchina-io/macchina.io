//
// Listener.h
//
// Library: JS/Bridge
// Package: Bridging
// Module:  Listener
//
// Definition of the Listener class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Bridge_Listener_INCLUDED
#define JS_Bridge_Listener_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/RemotingNG/Listener.h"


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API Listener: public Poco::RemotingNG::Listener
{
public:
	using Ptr = Poco::AutoPtr<Listener>;

	Listener();
		/// Creates a Listener.

	~Listener();
		/// Destroys the Listener.

	// Poco::RemotingNG::Listener
	void start();
	void stop();
	const std::string& protocol() const;
	std::string createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId);
	bool handlesURI(const std::string& uri);
	void registerObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject, Poco::RemotingNG::Skeleton::Ptr pSkeleton);
	void unregisterObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject);

	static const std::string PROTOCOL;
};


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_Listener_INCLUDED
