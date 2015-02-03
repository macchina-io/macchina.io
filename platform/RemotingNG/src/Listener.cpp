//
// Listener.cpp
//
// $Id: //poco/1.4/RemotingNG/src/Listener.cpp#2 $
//
// Library: RemotingNG
// Package: Transport
// Module:  Listener
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/Listener.h"
#include "Poco/Exception.h"


namespace Poco {
namespace RemotingNG {


Listener::Listener(const std::string& endPoint): _endPoint(endPoint)
{
	poco_assert_dbg (!_endPoint.empty());
}


Listener::~Listener()
{
}


} } // namespace Poco::RemotingNG
