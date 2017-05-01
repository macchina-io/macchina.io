//
// Identifiable.cpp
//
// $Id: //poco/1.7/RemotingNG/src/Identifiable.cpp#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  Identifiable
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/Identifiable.h"


namespace Poco {
namespace RemotingNG {


Identifiable::Identifiable()
{
}


Identifiable::Identifiable(const Identifiable::ObjectId& oid): 
	_remoting__oid(oid)
{
}


Identifiable::~Identifiable()
{
}


void Identifiable::remoting__init(const Identifiable::ObjectId& oid)
{
	if (_remoting__oid.empty())
	{
		_remoting__oid = oid;
	}
	else 
	{
		poco_assert_msg (_remoting__oid == oid, "Identifiable already initialized with different ID");
	}
}


void Identifiable::remoting__setURI(const Poco::URI& uri)
{
	std::string str = uri.toString();
	if (!str.empty())
	{
		if (str[str.length() - 1] == '/')
			str.resize(str.length() - 1);
	}
	_remoting__uri = str;
}


} } // namespace Poco::RemotingNG
