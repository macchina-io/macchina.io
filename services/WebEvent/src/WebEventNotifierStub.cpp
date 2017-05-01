//
// WebEventNotifierStub.cpp
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/WebEvent/WebEventNotifierStub.h"


namespace IoT {
namespace WebEvent {


WebEventNotifierStub::WebEventNotifierStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject):
	IoT::WebEvent::WebEventNotifierRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
}


WebEventNotifierStub::~WebEventNotifierStub()
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

