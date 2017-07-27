//
// NodeFactory.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: NodeFactory
// Module:  NodeFactory
//
// Definition of the NodeFactory class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_NodeFactory_INCLUDED
#define IoT_Dataflow_Engine_NodeFactory_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/Node.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API NodeFactory
	/// An abstract factory for creating Nodes.
	///
	/// Subclasses must override the createNode() method.
{
public:
	NodeFactory();
		/// Creates a NodeFactory.

	virtual ~NodeFactory();
		/// Destroys the NodeFactory.
	
	virtual Node::Ptr createNode(const std::string& type, const std::string& id, const AttributedObject& attrs, Scheduler& scheduler) = 0;
		/// Creates and returns a Node corresponding to the given type, with the given ID, attributes and Scheduler.

private:
	NodeFactory(const NodeFactory&);
	NodeFactory& operator = (const NodeFactory&);
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_NodeFactory_INCLUDED
