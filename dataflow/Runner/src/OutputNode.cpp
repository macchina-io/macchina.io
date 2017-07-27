//
// OutputNode.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: OutputNode
// Module:  OutputNode
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Runner/OutputNode.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


OutputNodeFactoryService::OutputNodeFactoryService()
{
}


OutputNodeFactoryService::~OutputNodeFactoryService()
{
}


IoT::Dataflow::Engine::Node::Ptr OutputNodeFactoryService::createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler)
{
	return new Output<double>(id, attrs);
}


const std::type_info& OutputNodeFactoryService::type() const
{
	return typeid(OutputNodeFactoryService);
}


bool OutputNodeFactoryService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(OutputNodeFactoryService).name());
	return name == otherType.name() || NodeFactoryService::isA(otherType);
}


} } } // namespace IoT::Dataflow::Runner
