//
// Deserializer.cpp
//
// $Id: //poco/1.6/RemotingNG/src/Deserializer.cpp#1 $
//
// Library: RemotingNG
// Package: Serialization
// Module:  Deserializer
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/Deserializer.h"


namespace Poco {
namespace RemotingNG {


Deserializer::Deserializer()
{
}


Deserializer::~Deserializer()
{
}


bool Deserializer::deserializeOptionalBegin(const std::string& name, bool isMandatory, bool& isSpecified)
{
	bool isNull;
	bool ret = deserializeNullableBegin(name, isMandatory, isNull);
	isSpecified = !isNull;
	return ret;
}


void Deserializer::deserializeOptionalEnd(const std::string& name)
{
	deserializeNullableEnd(name);
}


void Deserializer::pushAttribute(const std::string& /*attrNamespace*/, const std::string& /*attrName*/, bool /*isMandatory*/)
{
}


} } // namespace Poco::RemotingNG
