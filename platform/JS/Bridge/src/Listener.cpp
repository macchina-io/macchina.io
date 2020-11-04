//
// Listener.cpp
//
// Library: JS/Bridge
// Package: Bridging
// Module:  Listener
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Bridge/Listener.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Bridge {


const std::string Listener::PROTOCOL("jsbridge");


Listener::Listener():
	Poco::RemotingNG::Listener("local"s)
{
}


Listener::~Listener()
{
}


void Listener::start()
{
}


void Listener::stop()
{
}


const std::string& Listener::protocol() const
{
	return PROTOCOL;
}


std::string Listener::createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId)
{
	std::string uri("jsbridge://");
	uri += endPoint();
	uri += '/';
	uri += protocol();
	uri += '/';
	uri += typeId;
	uri += '/';
	uri += objectId;
	return uri;
}


bool Listener::handlesURI(const std::string& uri)
{
	return false;
}


void Listener::registerObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject, Poco::RemotingNG::Skeleton::Ptr pSkeleton)
{
}


void Listener::unregisterObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject)
{
}


} } } // namespace Poco::JS::Bridge
