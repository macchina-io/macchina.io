//
// CoreNodeFactoryService.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: CoreNodeFactoryService
// Module:  CoreNodeFactoryService
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Runner/CoreNodeFactoryService.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


CoreNodeFactoryService::CoreNodeFactoryService()
{
}


CoreNodeFactoryService::~CoreNodeFactoryService()
{
}


IoT::Dataflow::Engine::Node::Ptr CoreNodeFactoryService::createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler)
{
	return _coreNodeFactory.createNode(type, id, attrs, scheduler);
}


const std::type_info& CoreNodeFactoryService::type() const
{
	return typeid(CoreNodeFactoryService);
}


bool CoreNodeFactoryService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(CoreNodeFactoryService).name());
	return name == otherType.name() || NodeFactoryService::isA(otherType);
}


} } } // namespace IoT::Dataflow::Runner
