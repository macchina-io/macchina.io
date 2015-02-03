//
// EventListener.cpp
//
// $Id: //poco/1.4/RemotingNG/src/EventListener.cpp#2 $
//
// Library: RemotingNG
// Package: Transport
// Module:  EventListener
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
