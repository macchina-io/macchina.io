//
// IDatapointFactory.cpp
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  IDatapointFactory
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/IDatapointFactory.h"


namespace IoT {
namespace Datapoints {


IDatapointFactory::IDatapointFactory():
	Poco::OSP::Service()

{
}


IDatapointFactory::~IDatapointFactory()
{
}


bool IDatapointFactory::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Datapoints::IDatapointFactory).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IDatapointFactory::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Datapoints.DatapointFactory");
	return REMOTING__TYPE_ID;
}


const std::type_info& IDatapointFactory::type() const
{
	return typeid(IDatapointFactory);
}


} // namespace Datapoints
} // namespace IoT

