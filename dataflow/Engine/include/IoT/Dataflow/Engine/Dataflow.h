//
// Dataflow.h
//
// $Id$
//
// Definition of the Dataflow class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Dataflow_INCLUDED
#define IoT_Dataflow_Dataflow_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/AttributedObject.h"
#include "IoT/Dataflow/Engine/Node.h"
#include "IoT/Dataflow/Engine/Scheduler.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API Dataflow: public AttributedObject
	/// The Dataflow class contains a collection of Nodes, as well as a Scheduler.
{
public:
	typedef Poco::SharedPtr<Dataflow> Ptr;

	Dataflow();
		/// Creates the Dataflow.
		
	virtual ~Dataflow();
		/// Destroys the Dataflow.

	void addNode(Node::Ptr pNode);
		/// Adds a Node to the Dataflow.

	Node::Ptr node(const std::string& name) const;
		/// Returns the Node with the given name.
		///
		/// Throws a Poco::NotFoundException if no such node exists.

	Node::Ptr findNode(const std::string& name) const;
		/// Returns the Node with the given name, or
		/// null if no such node exists.
		
	void connect(const std::string& sourceNodeName, const std::string& outlet, const std::string& targetNodeName, const std::string& inlet);
		/// Connects the given outlet of the source node identified by sourceNodeName
		/// to the given inlet of the target node identified by targetNodeName.
	
	void start();
		/// Starts dataflow processing.
		
	void stop();
		/// Stops dataflow processing.
		
	Scheduler& scheduler();
		/// Returns the Scheduler used by the Dataflow.

private:
	Scheduler _scheduler;
	std::map<std::string, Node::Ptr> _nodes;
};


//
// inlines
//
inline Scheduler& Dataflow::scheduler()
{
	return _scheduler;
}


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Dataflow_INCLUDED
