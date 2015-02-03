//
// AttributedObject.h
//
// $Id: //poco/1.4/RemotingNG/src/AttributedObject.cpp#2 $
//
// Library: RemotingNG
// Package: ORB
// Module:  AttributedObject
//
// Definition of the AttributedObject class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/AttributedObject.h"
#include "Poco/Exception.h"


namespace Poco {
namespace RemotingNG {


AttributedObject::AttributedObject()
{
}


AttributedObject::~AttributedObject()
{
}

	
void AttributedObject::setAttribute(const std::string& name, const std::string& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_attributes[name] = value;
}

	
const std::string& AttributedObject::getAttribute(const std::string& name) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return it->second;
	else
		throw Poco::NotFoundException(name);
}

	
const std::string& AttributedObject::getAttribute(const std::string& name, const std::string& deflt) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	NameValueMap::const_iterator it = _attributes.find(name);
	if (it != _attributes.end())
		return it->second;
	else
		return deflt;
}


bool AttributedObject::hasAttribute(const std::string& name) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	NameValueMap::const_iterator it = _attributes.find(name);
	return it != _attributes.end();
}


} } // namespace Poco::RemotingNG
