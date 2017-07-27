//
// CoreNodeFactory.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: NodeFactory
// Module:  NodeFactory
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/CoreNodeFactory.h"
#include "IoT/Dataflow/Engine/FlowNodes.h"
#include "IoT/Dataflow/Engine/ArithmeticNodes.h"
#include "IoT/Dataflow/Engine/ComputationNodes.h"
#include "IoT/Dataflow/Engine/LogicalNodes.h"
#include "IoT/Dataflow/Engine/RelationalNodes.h"
#include "IoT/Dataflow/Engine/TimingNodes.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


CoreNodeFactory::CoreNodeFactory()
{
}


CoreNodeFactory::~CoreNodeFactory()
{
}


Node::Ptr CoreNodeFactory::createNode(const std::string& type, const std::string& id, const AttributedObject& attrs, Scheduler& scheduler)
{
	if (type == "core.arithmetic.add")
		return new IoT::Dataflow::Engine::Add<double>(id, attrs, scheduler);
	else if (type == "core.arithmetic.sub")
		return new IoT::Dataflow::Engine::Sub<double>(id, attrs, scheduler);
	else if (type == "core.arithmetic.mul")
		return new IoT::Dataflow::Engine::Mul<double>(id, attrs, scheduler);
	else if (type == "core.arithmetic.div")
		return new IoT::Dataflow::Engine::Div<double>(id, attrs, scheduler);
	else if (type == "core.arithmetic.mod")
		return new IoT::Dataflow::Engine::Mod<double>(id, attrs, scheduler);
	else if (type == "core.computation.const")
		return new IoT::Dataflow::Engine::Constant<double>(id, attrs, scheduler);
	else if (type == "core.computation.scale")
		return new IoT::Dataflow::Engine::Scale<double>(id, attrs, scheduler);
	else if (type == "core.computation.max")
		return new IoT::Dataflow::Engine::Max<double>(id, attrs, scheduler);
	else if (type == "core.computation.min")
		return new IoT::Dataflow::Engine::Min<double>(id, attrs, scheduler);
	else if (type == "core.computation.avg")
		return new IoT::Dataflow::Engine::Avg<double>(id, attrs, scheduler);
	else if (type == "core.computation.count")
		return new IoT::Dataflow::Engine::Count<double>(id, attrs, scheduler);
	else if (type == "core.computation.abs")
		return new IoT::Dataflow::Engine::Abs<double>(id, attrs, scheduler);
	else if (type == "core.computation.delta")
		return new IoT::Dataflow::Engine::Delta<double>(id, attrs, scheduler);
	else if (type == "core.computation.acc")
		return new IoT::Dataflow::Engine::Accumulate<double>(id, attrs, scheduler);
	else if (type == "core.logical.not")
		return new IoT::Dataflow::Engine::Not<bool>(id, attrs, scheduler);
	else if (type == "core.logical.and")
		return new IoT::Dataflow::Engine::And<bool>(id, attrs, scheduler);
	else if (type == "core.logical.or")
		return new IoT::Dataflow::Engine::Or<bool>(id, attrs, scheduler);
	else if (type == "core.logical.xor")
		return new IoT::Dataflow::Engine::Xor<bool>(id, attrs, scheduler);
	else if (type == "core.flow.threshold")
		return new IoT::Dataflow::Engine::Threshold<double>(id, attrs, scheduler);
	else if (type == "core.flow.gate")
		return new IoT::Dataflow::Engine::Gate<double>(id, attrs, scheduler);
	else if (type == "core.flow.splitter")
		return new IoT::Dataflow::Engine::Splitter<double>(id, attrs, scheduler);
	else if (type == "core.flow.change")
		return new IoT::Dataflow::Engine::ChangeTrigger<double>(id, attrs, scheduler);
	else if (type == "core.timing.stopwatch")
		return new IoT::Dataflow::Engine::Stopwatch<double>(id, attrs, scheduler);
	else if (type == "core.timing.clock")
		return new IoT::Dataflow::Engine::Clock<double>(id, attrs, scheduler);
	else
		return 0;
}


} } } // namespace IoT::Dataflow::Engine
