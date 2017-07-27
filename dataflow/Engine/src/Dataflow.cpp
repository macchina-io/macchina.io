//
// Dataflow.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Dataflow.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


Dataflow::Dataflow()
{
}


Dataflow::~Dataflow()
{
}


void Dataflow::addNode(Node::Ptr pNode)
{
	_nodes[pNode->id()] = pNode;
}


Node::Ptr Dataflow::node(const std::string& name) const
{
	auto it = _nodes.find(name);
	if (it != _nodes.end())
	{
		return it->second;
	}
	else throw Poco::NotFoundException(name);
}


Node::Ptr Dataflow::findNode(const std::string& name) const
{
	auto it = _nodes.find(name);
	if (it != _nodes.end())
	{
		return it->second;
	}
	else return nullptr;
}


void Dataflow::connect(const std::string& sourceNodeName, const std::string& outlet, const std::string& targetNodeName, const std::string& inlet)
{
	Node::Ptr pSourceNode = node(sourceNodeName);
	Node::Ptr pTargetNode = node(targetNodeName);
	pTargetNode->inlet(inlet)->connect(*pSourceNode->outlet(outlet));
}


void Dataflow::start()
{
	_scheduler.start();
}


void Dataflow::stop()
{
	_scheduler.stop();
}


} } } // namespace IoT::Dataflow::Engine
