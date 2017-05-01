//
// RotaryEncoderStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/RotaryEncoderStub.h"
#include "IoT/Devices/RotaryEncoderEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


RotaryEncoderStub::RotaryEncoderStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject):
	IoT::Devices::RotaryEncoderRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->buttonStateChanged += Poco::delegate(this, &RotaryEncoderStub::event__buttonStateChanged);
	_pServiceObject->countChanged += Poco::delegate(this, &RotaryEncoderStub::event__countChanged);
}


RotaryEncoderStub::~RotaryEncoderStub()
{
	try
	{
		_pServiceObject->buttonStateChanged -= Poco::delegate(this, &RotaryEncoderStub::event__buttonStateChanged);
		_pServiceObject->countChanged -= Poco::delegate(this, &RotaryEncoderStub::event__countChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string RotaryEncoderStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void RotaryEncoderStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new RotaryEncoderEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool RotaryEncoderStub::remoting__hasEvents() const
{
	return true;
}


void RotaryEncoderStub::event__buttonStateChanged(const bool& data)
{
	buttonStateChanged(this, data);
}


void RotaryEncoderStub::event__countChanged(const Poco::Int32& data)
{
	countChanged(this, data);
}


} // namespace Devices
} // namespace IoT

