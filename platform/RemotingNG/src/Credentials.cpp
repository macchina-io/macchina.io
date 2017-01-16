//
// Credentials.cpp
//
// $Id$
//
// Library: RemotingNG
// Package: Transport
// Module:  Credentials
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/Credentials.h"


namespace Poco {
namespace RemotingNG {


Credentials::Credentials()
{
}


Credentials::Credentials(const Credentials& other):
	AttributedObject(other)
{
}

	
Credentials& Credentials::operator = (const Credentials& other)
{
	AttributedObject::operator = (other);
	return *this;
}

	
Credentials::~Credentials()
{
}


} } // namespace Poco::RemotingNG
