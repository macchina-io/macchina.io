//
// NodeFactoryService.h
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: NodeFactoryService
// Module:  NodeFactoryService
//
// Definition of the NodeFactoryService class.
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Runner_NodeFactoryService_INCLUDED
#define IoT_Dataflow_Runner_NodeFactoryService_INCLUDED


#include "IoT/Dataflow/Runner/Runner.h"
#include "IoT/Dataflow/Engine/Node.h"
#include "Poco/OSP/Service.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


class IoTDataflowRunner_API NodeFactoryService: public Poco::OSP::Service
	/// An abstract factory for creating Nodes, as Poco::OSP::Service.
	///
	/// Subclasses must override the createNode() method.
	///
	/// NodeFactoryService allows dynamic registration and discovery of Node 
	/// classes using the OSP ServiceRegistry.
	///
	/// An instance of NodeFactoryService must be registered with the
	/// ServiceRegistry with the property "io.macchina.dataflow.nodetype" set
	/// to the name or namespace of the node type, as used by 
	/// IoT::Dataflow::Engine::NodeFactory. Therefore, a NodeFactoryService
	/// instance can handle a single node type, or a whole family of node
	/// types. For example, a NodeFactoryService registered for "core.arithmetic.add"
	/// will handle only the IoT::Dataflow::Engine::Add node type. 
	/// A NodeFactoryService registered for "core.arithmetic" will handle all arithmetic
	/// node types, e.g. "add", "sub", "mul", "div" and "mod".
	/// A NodeFactoryService registered for "core" will handle all core node types.
	///
	/// When searching for a matching factory for a certain type, the search begins
	/// with the full type name. If no service is found, the last part of the type
	/// is stripped off and the search is repeated. 
{
public:
	typedef Poco::AutoPtr<NodeFactoryService> Ptr;

	NodeFactoryService();
		/// Creates a NodeFactoryService.

	~NodeFactoryService();
		/// Destroys the NodeFactoryService.
	
	virtual IoT::Dataflow::Engine::Node::Ptr createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler) = 0;
		/// Creates and returns a Node corresponding to the given type, with the given ID, attributes and Scheduler.

	// Service
	const std::type_info& type() const;	
	bool isA(const std::type_info& otherType) const;
};


} } } // namespace IoT::Dataflow::Runner


#endif // IoT_Dataflow_Runner_NodeFactoryService_INCLUDED
