//
// IWebEventNotifier.cpp
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  IWebEventNotifier
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/WebEvent/IWebEventNotifier.h"


namespace IoT {
namespace WebEvent {


IWebEventNotifier::IWebEventNotifier():
	Poco::OSP::Service(),
	event()
{
}


IWebEventNotifier::~IWebEventNotifier()
{
}


bool IWebEventNotifier::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::WebEvent::IWebEventNotifier).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IWebEventNotifier::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.WebEvent.WebEventNotifier");
	return REMOTING__TYPE_ID;
}


const std::type_info& IWebEventNotifier::type() const
{
	return typeid(IWebEventNotifier);
}


} // namespace WebEvent
} // namespace IoT

