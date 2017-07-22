//
// CoreNodeFactory.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: NodeFactory
// Module:  CoreNodeFactory
//
// Definition of the CoreNodeFactory class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_CoreNodeFactory_INCLUDED
#define IoT_Dataflow_Engine_CoreNodeFactory_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/NodeFactory.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API CoreNodeFactory: public NodeFactory
	/// The NodeFactory for the built-in core Node types.
	///
	/// The following Node types are supported:
	///
	///     Type                           Node Class
	///     ---------------------------------------------------------------------------
	///     core.arithmetic.add            IoT::Dataflow::Engine::Add<double>
	///     core.arithmetic.sub            IoT::Dataflow::Engine::Sub<double>
	///     core.arithmetic.mul            IoT::Dataflow::Engine::Mul<double>
	///     core.arithmetic.div            IoT::Dataflow::Engine::Div<double>
	///     core.arithmetic.mod            IoT::Dataflow::Engine::Mod<double>
	///     core.computation.const         IoT::Dataflow::Engine::Constant<double>
	///     core.computation.scale         IoT::Dataflow::Engine::Scale<double>
	///     core.computation.max           IoT::Dataflow::Engine::Max<double>
	///     core.computation.min           IoT::Dataflow::Engine::Min<double>
	///     core.computation.avg           IoT::Dataflow::Engine::Avg<double>
	///     core.computation.count         IoT::Dataflow::Engine::Count<double>
	///     core.computation.abs           IoT::Dataflow::Engine::Abs<double>
	///     core.computation.delta         IoT::Dataflow::Engine::Delta<double>
	///     core.computation.acc           IoT::Dataflow::Engine::Accumulate<double>
	///     core.logical.not               IoT::Dataflow::Engine::Not<bool>
	///     core.logical.and               IoT::Dataflow::Engine::And<bool>
	///     core.logical.or                IoT::Dataflow::Engine::Or<bool>
	///     core.logical.xor               IoT::Dataflow::Engine::Xor<bool>
	///     core.flow.threshold            IoT::Dataflow::Engine::Threshold<double>
	///     core.flow.gate                 IoT::Dataflow::Engine::Gate<double>
	///     core.flow.splitter             IoT::Dataflow::Engine::Splitter<double>
	///     core.flow.change               IoT::Dataflow::Engine::ChangeTrigger<double>
	///     core.timing.stopwatch          IoT::Dataflow::Engine::Stopwatch<double>
	///     core.timing.clock              IoT::Dataflow::Engine::Clock<double>
{
public:
	CoreNodeFactory();
		/// Creates a CoreNodeFactory.

	~CoreNodeFactory();
		/// Destroys the CoreNodeFactory.
	
	// NodeFactory
	Node::Ptr createNode(const std::string& type, const std::string& id, const AttributedObject& attrs, Scheduler& scheduler);
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_CoreNodeFactory_INCLUDED
