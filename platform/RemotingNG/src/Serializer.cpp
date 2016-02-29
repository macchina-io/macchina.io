//
// Serializer.cpp
//
// $Id: //poco/1.7/RemotingNG/src/Serializer.cpp#1 $
//
// Library: RemotingNG
// Package: Serialization
// Module:  Serializer
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/Serializer.h"


namespace Poco {
namespace RemotingNG {


Serializer::Serializer()
{
}


Serializer::~Serializer()
{
}


void Serializer::serializeOptionalBegin(const std::string& name, bool isSpecified)
{
	serializeNullableBegin(name, !isSpecified);
}


void Serializer::serializeOptionalEnd(const std::string& name)
{
	serializeNullableEnd(name);
}


void Serializer::pushAttribute(const std::string&, const std::string&)
{
}


void Serializer::registerNamespace(const std::string&)
{
}


} } // namespace Poco::RemotingNG
