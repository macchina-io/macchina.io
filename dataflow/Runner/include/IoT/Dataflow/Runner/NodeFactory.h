//
// NodeFactory.h
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: NodeFactory
// Module:  NodeFactory
//
// Definition of the NodeFactory class.
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Runner_CoreNodeFactory_INCLUDED
#define IoT_Dataflow_Runner_CoreNodeFactory_INCLUDED


#include "IoT/Dataflow/Runner/Runner.h"
#include "IoT/Dataflow/Engine/NodeFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


class IoTDataflowRunner_API NodeFactory: public IoT::Dataflow::Engine::NodeFactory
	/// This class implements a "meta" NodeFactory that uses NodeFactoryService
	/// objects registered with the ServiceRegistry to create nodes.
{
public:
	NodeFactory(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates a NodeFactory with the given context.

	~NodeFactory();
		/// Destroys the NodeFactory.
	
	// NodeFactory
	IoT::Dataflow::Engine::Node::Ptr createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


} } } // namespace IoT::Dataflow::Runner


#endif // IoT_Dataflow_Runner_CoreNodeFactory_INCLUDED
