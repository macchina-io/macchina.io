//
// NodeFactoryService.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: NodeFactoryService
// Module:  NodeFactoryService
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Runner/NodeFactoryService.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


NodeFactoryService::NodeFactoryService()
{
}


NodeFactoryService::~NodeFactoryService()
{
}


const std::type_info& NodeFactoryService::type() const
{
	return typeid(NodeFactoryService);
}


bool NodeFactoryService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(NodeFactoryService).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}

	
} } } // namespace IoT::Dataflow::Runner
