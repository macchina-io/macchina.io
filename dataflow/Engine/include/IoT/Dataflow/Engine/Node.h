//
// Node.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Node
// Module:  Node
//
// Definition of the Node class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_Node_INCLUDED
#define IoT_Dataflow_Engine_Node_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/AttributedObject.h"
#include "IoT/Dataflow/Engine/Inlet.h"
#include "IoT/Dataflow/Engine/Outlet.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API Node: public AttributedObject, public Poco::RefCountedObject
	/// The base class for all processing nodes.
	///
	/// A Node has a number of inlets and outlets. 
	/// Processing is triggered when the value of an
	/// inlet changes. This will trigger outlets, which
	/// will again trigger any connected processing nodes.
{
public:
	typedef Poco::AutoPtr<Node> Ptr;

	Node(const std::string& id);
		/// Creates a Node with the given ID.

	Node(const std::string& id, const AttributedObject& attrs);
		/// Creates a Node with the given ID and attributes.
		
	~Node();
		/// Destroys the Node.
	
	AbstractInlet::Ptr inlet(const std::string& name);
		/// Returns the inlet with the given name.
		///
		/// Throws a Poco::NotFoundException if no inlet with 
		/// the given name exists.

	AbstractOutlet::Ptr outlet(const std::string& name);
		/// Returns the outlet with the given name.
		///
		/// Throws a Poco::NotFoundException if no outlet with 
		/// the given name exists.

	const std::string& id() const;
		/// Returns the ID of the Node.

	const std::vector<AbstractInlet::Ptr>& inlets() const;
		/// Returns the collection of inlets.
	
	const std::vector<AbstractOutlet::Ptr>& outlets() const;
		/// Returns the collection of outlets.
		
protected:
	void addInlet(AbstractInlet::Ptr pInlet);
		/// Adds the given inlet.
	
	void addOutlet(AbstractOutlet::Ptr pOutlet);
		/// Adds the given outlet.
	
private:
	Node();
	Node(const Node&);
	Node& operator = (const Node&);

	std::string _id;
	std::vector<AbstractInlet::Ptr> _inlets;
	std::vector<AbstractOutlet::Ptr> _outlets;
};


//
// inlines
//


inline const std::string& Node::id() const
{
	return _id;
}


inline const std::vector<AbstractInlet::Ptr>& Node::inlets() const
{
	return _inlets;
}


inline const std::vector<AbstractOutlet::Ptr>& Node::outlets() const
{
	return _outlets;
}


inline void Node::addInlet(AbstractInlet::Ptr pInlet)
{
	_inlets.push_back(pInlet);
}


inline void Node::addOutlet(AbstractOutlet::Ptr pOutlet)
{
	_outlets.push_back(pOutlet);
}


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_Node_INCLUDED
