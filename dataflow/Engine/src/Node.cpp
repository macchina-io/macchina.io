//
// Node.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Node
// Module:  Node
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Node.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


Node::Node(const std::string& id):
	_id(id)
{
}


Node::Node(const std::string& id, const AttributedObject& attrs):
	AttributedObject(attrs),
	_id(id)
{
}


Node::~Node()
{
}


AbstractInlet::Ptr Node::inlet(const std::string& name)
{
	for (auto pInlet: _inlets)
	{
		if (pInlet->name() == name)
			return pInlet;
	}
	throw Poco::NotFoundException("inlet", name);
}


AbstractOutlet::Ptr Node::outlet(const std::string& name)
{
	for (auto pOutlet: _outlets)
	{
		if (pOutlet->name() == name)
			return pOutlet;
	}
	throw Poco::NotFoundException("outlet", name);
}


} } } // namespace IoT::Dataflow::Engine
