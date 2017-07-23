//
// NodeFactory.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: NodeFactory
// Module:  NodeFactory
//
// Copyright (c) 2017, Applied Informatics Software Runnerering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Runner/NodeFactory.h"
#include "IoT/Dataflow/Runner/NodeFactoryService.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"


namespace IoT {
namespace Dataflow {
namespace Runner {


NodeFactory::NodeFactory(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


NodeFactory::~NodeFactory()
{
}


IoT::Dataflow::Engine::Node::Ptr NodeFactory::createNode(const std::string& type, const std::string& id, const IoT::Dataflow::Engine::AttributedObject& attrs, IoT::Dataflow::Engine::Scheduler& scheduler)
{
	IoT::Dataflow::Engine::Node::Ptr pNode;

	std::string queryType = type;
	while (!queryType.empty())
	{
		_pContext->logger().debug("Looking for NodeFactoryService for Node type \"%s\"...", queryType);
		std::string query = "io.macchina.dataflow.nodeType == \"";
		query += queryType;
		query += "\"";
		
		std::vector<Poco::OSP::ServiceRef::Ptr> refs;
		_pContext->registry().find(query, refs);
		if (!refs.empty())
		{
			_pContext->logger().debug("Found %z results for Node type \"%s\".", refs.size(), queryType);
			for (auto& r: refs)
			{
				NodeFactoryService::Ptr pFactory = r->castedInstance<NodeFactoryService>();
				pNode = pFactory->createNode(type, id, attrs, scheduler);
				if (pNode) 
				{
					_pContext->logger().debug("Successfully created Node type \"%s\".", type);
					break;
				}
			}
		}
		
		std::string::size_type pos = queryType.rfind('.');
		if (pos == std::string::npos)
			queryType.clear();
		else
			queryType.resize(pos);
	}

	return pNode;
}


} } } // namespace IoT::Dataflow::Runner
