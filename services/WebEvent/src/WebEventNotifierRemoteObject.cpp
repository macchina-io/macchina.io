//
// WebEventNotifierRemoteObject.cpp
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/WebEvent/WebEventNotifierRemoteObject.h"


namespace IoT {
namespace WebEvent {


WebEventNotifierRemoteObject::WebEventNotifierRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject):
	IoT::WebEvent::IWebEventNotifier(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


WebEventNotifierRemoteObject::~WebEventNotifierRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace WebEvent
} // namespace IoT

