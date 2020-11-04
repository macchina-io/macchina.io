//
// EventListener.cpp
//
// Library: RemotingNG
// Package: Transport
// Module:  EventListener
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/RemotingNG/EventListener.h"


namespace Poco {
namespace RemotingNG {


EventListener::EventListener(const std::string& endPoint):
	Listener(endPoint)
{
}


EventListener::~EventListener()
{
}


} } // namespace Poco::RemotingNG
