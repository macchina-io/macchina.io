//
// RotaryEncoderRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/RotaryEncoderRemoteObject.h"
#include "IoT/Devices/RotaryEncoderEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


RotaryEncoderRemoteObject::RotaryEncoderRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject):
	IoT::Devices::IRotaryEncoder(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->buttonStateChanged += Poco::delegate(this, &RotaryEncoderRemoteObject::event__buttonStateChanged);
	_pServiceObject->countChanged += Poco::delegate(this, &RotaryEncoderRemoteObject::event__countChanged);
}


RotaryEncoderRemoteObject::~RotaryEncoderRemoteObject()
{
	try
	{
		_pServiceObject->buttonStateChanged -= Poco::delegate(this, &RotaryEncoderRemoteObject::event__buttonStateChanged);
		_pServiceObject->countChanged -= Poco::delegate(this, &RotaryEncoderRemoteObject::event__countChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string RotaryEncoderRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void RotaryEncoderRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new RotaryEncoderEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool RotaryEncoderRemoteObject::remoting__hasEvents() const
{
	return true;
}


void RotaryEncoderRemoteObject::event__buttonStateChanged(const bool& data)
{
	buttonStateChanged(this, data);
}


void RotaryEncoderRemoteObject::event__countChanged(const Poco::Int32& data)
{
	countChanged(this, data);
}


} // namespace Devices
} // namespace IoT

